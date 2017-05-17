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

    cli
_stop:
    hlt
    jmp _stop

.global GDT_flush
GDT_flush:
    movl 4(%esp), %eax
    lgdt (%eax)
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
    ljmp $0x08, $_flush
_flush:
    ret

.global IDT_flush
IDT_flush:
    movl 4(%esp), %eax
    lidt (%eax)
    ret

.section .bss
.space 1 * 1024 * 1024

kernel_stack:
