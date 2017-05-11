CC = gcc
AS = as
LD = ld

CFLAGS = -m32 -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore
ASFLAGS = --32
LDFLAGS = -melf_i386

objects = \
	loader.o \
	kernel.o \
	tty.o \
	gdt.o \
	port.o

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
	grub2-mkrescue --output $@ iso
	rm -Rf iso/

run: zinux.iso
	VirtualBox --startvm Zinux

install: zinux.bin
	cp $< /boot/zinux.bin

clean:
	rm -Rf $(objects) zinux.bin zinux.iso
