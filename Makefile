c-files=$(wildcard kernel/*.c drivers/*.c)
header-files=$(wildcard kernel/*.h drivers/*.h)
object-files=${c-files:.c=.o}

run:os-image
	qemu-system-x86_64 os-image
os-image:boot/boot_sect.bin kernel.bin
	cat $^>$@
boot/boot_sect.bin:boot/boot_sect.asm
	nasm $< -f bin -o $@
kernel.bin:kernel/kernel_entry.o ${object-files}
	ld -o $@ -Ttext 0x1000 $^ --oformat binary
kernel/kernel_entry.o:kernel/kernel_entry.asm
	nasm $< -f elf64 -o $@
%.o:%.c ${header-files}
	gcc -c -ffreestanding $< -o $@
%.bin:%.asm
	nasm $< -f bin -o $@
clean:
	rm *.bin *.o os-image *.dis
	rm kernel/*.o boot/*.bin drivers/*.o

