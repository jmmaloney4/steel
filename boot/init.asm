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
; init.asm - Steel Bootloader Initilization Routines
;
; -----------------------------------------------------------------------------

USE16

;kinit:
    cli
    xor eax, eax        ; clear registers
    xor ebx, ebx
    xor edx, edx
    xor esi, esi
    xor edi, edi
    xor ebp, ebp
    mov ds, ax          ; clear segment registers
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax
    mov esp, 0x8000     ; set stack pointer to safe position

    
    ; Make sure the screen is set to 80x25 color text mode
	;mov ax, 0x0003			; Set to normal (80x25 text) video mode
	;int 0x10

    ; Hide the hardware cursor (interferes with print_string_16 if called earlier)
	;mov ax, 0x0200			; VIDEO - SET CURSOR POSITION
	;mov bx, 0x0000			; Page number
	;mov dx, 0x2000			; Row / Column
	;int 0x10

    ; mov si, [msg_init]
    ; call print_string_SI_16
    ;
    ; mov si, [msg_detecting]
    ; call print_string_SI_16

    sti
kinit:
    mov ah, 0x0E
    
    mov al, 'H'
    int 0x10
    
    mov al, 'e'
    int 0x10

    ret

; msg_init: db 'Initializing...', 0x0D, 0x0A, 0
; msg_detecting: db 'Detecting 64-Bit', 0x0D, 0x0A, 0

print_string_SI_16:
    pusha
    mov ah, 0x0E
 .loop:
    lodsb
    
    cmp al, 0
    je .done
    
    int 0x10

 .done:
    popa
    ret


