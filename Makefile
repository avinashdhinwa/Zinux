CC = gcc
AS = as
LD = ld

CFLAGS = -m32 -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore -g
ASFLAGS = --32 -g
LDFLAGS = -melf_i386

objects = \
	loader.o \
	kernel.o \
	tty.o \
	gdt.o \
	port.o \
	interrupts.o \
	idt.o \
	irq.o

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.S
	$(AS) $(ASFLAGS) -o $@ -c $<

zinux.bin: linker.ld $(objects)
	$(LD) $(LDFLAGS) -T $< -o $@ $(objects)

zinux.iso: zinux.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo 'menuentry "Zinux" {' >> iso/boot/grub/grub.cfg
	echo '    multiboot /boot/zinux.bin' >> iso/boot/grub/grub.cfg
	echo '    boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output $@ iso
	rm -Rf iso/

run: zinux.iso
	qemu-system-x86_64 -boot d -cdrom zinux.iso -m 512

debug: zinux.iso
	qemu-system-x86_64 -boot d -cdrom zinux.iso -m 512 -s -S &
	gdb zinux.bin -ex "target remote :1234"

install: zinux.bin
	cp $< /boot/zinux.bin

clean:
	rm -Rf $(objects) zinux.bin zinux.iso
