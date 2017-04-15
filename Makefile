CC = gcc
AS = as
LD = ld

CFLAGS = -m32 -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore
ASFLAGS = --32
LDFLAGS = -melf_i386

objects = loader.o kernel.o

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.S
	$(AS) $(ASFLAGS) -o $@ -c $<

zinux.bin: linker.ld $(objects)
	$(LD) $(LDFLAGS) -T $< -o $@ $(objects)

install: zinux.bin
	cp $< /boot/zinux.bin

clean:
	rm *.o zinux.bin
