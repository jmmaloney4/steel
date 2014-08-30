[bits 16]
[org 0x7c00]

mov [BOOT_DRIVE], dl    ; Store Boot Drive Info

mov bp, 0x8000          ; Set Stack At Safe Position
mov sp, bp              ;

;mov bx, msg
;call print_string_16

mov bx, [msg_initializing]
call print_string_16

call enter_32_bit_pm

jmp $   ; hang

msg: db 'Hello, World!', 0x0

; Boot Drive Variable
BOOT_DRIVE: db 0

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

    mov al, [bx]

    cmp al, 0
    je .done

    int 0x10

    jc .error

    add bx, 1   ; increment address of char

    jmp .loop

 .done:

    popa
    ret

 .error:
    mov bx, .error_msg
    call print_string_16    ; try calling this function again, may not work

    jmp $                   ; hang

 .error_msg:
    db 'Error Printing String'

enter_32_bit_pm:

    cli     ; disable interupts - no interupt vector table

    lgdt [gdt_descriptor] ; Load the descriptor table

    mov eax, cr0
    or eax, 00000001b
    mov cr0, eax

    jmp CODE_SEG:protected_mode

; GDT - Global Descriptor Table
gdt_start:

gdt_null:
    dd 0x0  ; 8 bytes of zeros
    dd 0x0  ; each dd (double word) is 4 bytes

gdt_code:
    dw 0xffff   ; Limit - part 1
    dw 0x0      ; Base which is 0
    db 0x0      ; Base - part 2
    db 10011010b    ; Flags - part 1
    db 11001111b    ; Flags - part 2 and Limit part 2 xxxx|xxxx
    db 0x0      ; Base - part 3

; same as gdt_code except for code byte in flags
gdt_data:
    dw 0xffff   ; Limit - part 1
    dw 0x0      ; Base which is 0
    db 0x0      ; Base - part 2
    db 10010010b    ; Flags - part 1
    db 11001111b    ; Flags - part 2 and Limit part 2 xxxx|xxxx
    db 0x0      ; Base - part 3

gdt_end:    ; To calculate the size of the gdt

gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; size of GDT

    dd gdt_start                ; GDT Refrence

; Constants About GDT
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

[bits 32]

protected_mode:


msg_initializing: db 'Initializing 32-Bit Protected Mode', 0

; Padding and magic number.
times 510 - ($-$$) db 0
dw 0xaa55
