#!bin/bash
set e

echo "Building..." 
echo ""

echo "Beginning NASM Compilation..."
nasm src/bootloader.asm -f elf32 -o build/bin/bootloader.o
nasm src/kernel/memory/gdt/gdt.asm -f elf32 -o build/bin/gdt.o
nasm src/kernel/memory/idt/idt.asm -f elf32 -o build/bin/idt.o
nasm src/kernel/memory/isrs/isrs.asm -f elf32 -o build/bin/isrs.o
nasm src/kernel/memory/irq/irq.asm -f elf32 -o build/bin/irq.o
nasm
echo "Done..." 
echo ""

echo "Beginning Clang Compilation..."
clang -c -target i686-none-elf -o build/bin/kernelmain.o -ffreestanding -mno-sse -Wall src/kernel/kernelmain.c
echo "Done..." 
echo ""

echo "Beginning Linker..."
ld.lld -T src/linker.ld -o build/bin/os.bin -static -nostdlib build/bin/*.o
echo "Done..."
echo ""

echo "Beginning ISO Creation..."
cp build/bin/os.bin iso/boot/os.bin
grub-mkrescue -o build/bin/os.iso iso
echo "Done..."
echo ""

echo "Booting..."
qemu-system-i386 -cdrom build/bin/os.iso
echo "Done..."
echo ""

echo "Beginning Clean Up..."
rm build/bin/*.*
rm iso/boot/*.bin
echo "Finished..." 
echo ""