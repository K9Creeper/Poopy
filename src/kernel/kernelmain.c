#include "./includes.h"
#include "./gui/cmd.h"

// memory managment
#include "./memory/gdt/gdt.h"
#include "./memory/idt/idt.h"
#include "./memory/isrs/isrs.h"
#include "./memory/irq/irq.h"

// system calls
#include "./system/input/keyboard.h"
#include "./system/timer.h"


void kernelmain(void)
{
  terminal_init();

  // memory
  gdt_install();
  idt_install();
  isrs_install();
  irq_install();

  // system
  keyboard_install();
  timer_install();

  asm volatile("sti");
  
  cmd_install_keyboard();
  
  for(;;)
    {
      
      asm volatile("hlt");
    }
}