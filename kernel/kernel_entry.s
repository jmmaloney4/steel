; Simple File To Call Kernel Main Function
; Because Bootloader Will Just Jump Here

start:
    extern _kmain

    call _kmain

    jmp $
