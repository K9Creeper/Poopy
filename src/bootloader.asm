[BITS 32]
MBALIGN  equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ; provide memory map
MBFLAGS  equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + MBFLAGS)   ; checksum of above, to prove we are multiboot

section .multiboot
  align 4
  dd MAGIC
  dd MBFLAGS
  dd CHECKSUM 
  dd 0


section .bss
system_stack:
resb 8192 ; 8 KiB

section .text
  global _start

_start:
  mov esp, system_stack ; create / alloc stack
  
  extern kernelmain
  call kernelmain



; signitures
times 510-($ - $$) db 0
dw 0xAA55