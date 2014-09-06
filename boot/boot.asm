; -----------------------------------------------------------------------------
;
; The MIT License (MIT)
;
; Copyright (c) 2014 Jack Maloney
;
; Permission is hereby granted, free of charge, to any person obtaining a copy
; of this software and associated documentation files (the "Software"), to deal
; in the Software without restriction, including without limitation the rights
; to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
; copies of the Software, and to permit persons to whom the Software is
; furnished to do so, subject to the following conditions:
;
; The above copyright notice and this permission notice shall be included in all
; copies or substantial portions of the Software.
;
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
; AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
; LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
; SOFTWARE.
;
; -----------------------------------------------------------------------------

; -----------------------------------------------------------------------------
;
; Steel Bootloader
;
; -----------------------------------------------------------------------------

[bits 16]
[org 0x7c00]

start:

    mov [BOOT_DRIVE], dl    ; Store Boot Drive Info

    mov bp, 0xa000          ; Set Stack At Safe Position
    mov sp, bp              ;

    ;call enableA20          ; enable the A20 gate
    
    ; Notify BIOS of our intent to run in 64-bit long mode
    mov ax, 0xec00
    mov bl, 2
    int 0x15
    
    mov bx, MSG_INIT
    call print_string_16

    ; Load Kernel
    mov dh, 20      ; load 20 segments for out kernel

    mov bx, 0x0     ; set es indirectly
    mov es, bx
    mov bx, KERNEL_POS     ; (20 x 512) + 1000 is 10,240 and 0x7c00 is 31,744, so we still have some space

    mov dl, [BOOT_DRIVE] ; set drive to read from

    call disk_load_16   ; read the kernel

    call enter_32_bit_pm

    jmp $   ; hang


BOOT_DRIVE: db 0
KERNEL_POS: equ 0x1000
MSG_INIT: db 'Initializing...', 0

; load dh number of sectors
; buffer at es:bx
; dl = drive to read from
; reads from second sector = sector after boot sector
disk_load_16:
    pusha

    ;push dh         ; save number of sectors

    mov ah, 0x02    ; read sectors
    mov al, dh      ; dh sectors
    mov ch, 0x00    ; cylinder 0
    mov dh, 0x00    ; head 0
    mov cl, 0x02    ; read from second sector (sectors are 1-based)

    int 0x13        ; do read

    jc .error

    popa
    ret

 .error:
    mov bx, .error_msg
    call print_string_16

 .error_msg:
    db 'Error Reading From Disk', 0

; print string in refrenced by bx
print_string_16:
    pusha
    mov ah, 0x0e    ; teletype mode
 .loop:

    mov al, [bx]    ; load char to print
    add bx, 1       ; increment address of char

    cmp al, 0   ; check if we are done
    je .done    ;

    int 0x10

    jmp .loop   ; loop

 .done:

    popa
    ret

enter_32_bit_pm:

    cli     ; disable interupts - no interupt table

    lgdt [GDT32.Ptr] ; Load the descriptor table

    mov eax, cr0
    or eax, 00000001b
    mov cr0, eax

    jmp GDT32.Code:protected_mode ; clear the pipline by doing a far jump

; GDT - Global Descriptor Table
GDT32:

.Null: equ $ - GDT32
    dq 0x0  ; 8 bytes of zeros
    dq 0x0  ; each dd (double word) is 4 bytes

.Code: equ $ - GDT32
    dw 0xffff   ; Limit - part 1
    dw 0x0      ; Base which is 0
    db 0x0      ; Base - part 2
    db 10011010b    ; Flags - part 1
    db 11001111b    ; Flags - part 2 and Limit part 2 xxxx|xxxx
    db 0x0      ; Base - part 3

; same as gdt_code except for code byte in flags
.Data: equ $ - GDT32
    dw 0xffff   ; Limit - part 1
    dw 0x0      ; Base which is 0
    db 0x0      ; Base - part 2
    db 10010010b    ; Flags - part 1
    db 11001111b    ; Flags - part 2 and Limit part 2 xxxx|xxxx
    db 0x0      ; Base - part 3

.End:    ; To calculate the size of the gdt

.Ptr:
    dw $ - GDT32 - 1  ; size of GDT

    dq GDT32          ; GDT Refrence

; Enable the A20 gate
enableA20:
	in al, 0x64
	test al, 0x02
	jnz enableA20
	mov al, 0xD1
	out 0x64, al
 .check:
	in al, 0x64
	test al, 0x02
	jnz .check
	mov al, 0xDF
	out 0x60, al

; -----------------------------------------------------------------------------
; 32-Bit PROTECTED MODE

[bits 32]

protected_mode:

    call enter_64_bit_lm    ; go into long mode

    jmp $                   ; hang

enter_64_bit_lm:

    mov ecx, 0xC0000080          ; Set the C-register to 0xC0000080, which is the EFER MSR.
    rdmsr                        ; Read from the model-specific register.
    or eax, 1 << 8               ; Set the LM-bit which is the 9th bit (bit 8).
    wrmsr                        ; Write to the model-specific register.

    mov eax, cr0                 ; Set the A-register to control register 0.
    or eax, 1 << 31              ; Set the PG-bit, which is the 32nd bit (bit 31).
    mov cr0, eax                 ; Set control register 0 to the A-register.

    jmp long_mode     ; jump to long mode

; -----------------------------------------------------------------------------
; 32-Bit LONG MODE

long_mode:

    lgdt [GDT64.Ptr]    ; Load 64-Bit Descriptor Table

    jmp GDT64.Code:long_mode_64

; -----------------------------------------------------------------------------
; 64-Bit LONG MODE

[bits 64]

; Launch The Kernel
long_mode_64:
; Fall Through
launch_kernel_64:
    call KERNEL_POS     ; where we loaded our kernel in memory

    jmp $               ; hang


GDT64:

 .Null: equ $ - GDT64
    dq 0x0
    dq 0x0

 .Code: equ $ - GDT64
    dw 0x0
    dw 0x0
    db 0x0
    db 10011000b
    db 00100000b
    db 0x0

 .Data: equ $ - GDT64
    dw 0x0
    dw 0x0
    db 0x0
    db 10010000b
    db 00000000b
    db 0x0

 .End:

 .Ptr:
    dw $ - GDT64 - 1
    dq GDT64

; Padding and magic number.
times 510 - ($-$$) db 0
dw 0xaa55
