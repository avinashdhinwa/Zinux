.set MAGIC, 0x1BADB002
.set FLAGS, (1 << 0 | 1 << 1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .text
.extern kernelMain
.global loader

loader:
    mov $kernel_stack, %esp
    push %eax
    push %ebx
    call kernelMain

_stop:
    cli
    hlt
    jmp _stop

.global GDT_flush
.extern pGDT
GDT_flush:
    lgdt (pGDT)
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
    ljmp $0x08, $_flush
_flush:
    ret

.section .bss
.space 2 * 1024 * 1024

kernel_stack:
