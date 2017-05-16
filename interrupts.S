.set IRQ_BASE, 0x20

.section .text

.extern IRQHandler

.macro ExceptionHandler num
.global ExceptionHandler\num
ExceptionHandler\num:
    movb $\num, (IRQNumber)
    jmp interrupt
.endm

.macro InterruptHandler num
.global IRQHandler\num
IRQHandler\num:
    movb $\num + IRQ_BASE, (IRQNumber)
    jmp interrupt
.endm

ExceptionHandler 00
ExceptionHandler 01
ExceptionHandler 02
ExceptionHandler 03

InterruptHandler 00
InterruptHandler 01
InterruptHandler 02
InterruptHandler 03

interrupt:
    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    pushl %esp
    push (IRQNumber)
    call IRQHandler
    movl %eax, %esp

    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa

.global IRQHandlerIgnore
IRQHandlerIgnore:
    iret

.data
    IRQNumber: .byte 0
