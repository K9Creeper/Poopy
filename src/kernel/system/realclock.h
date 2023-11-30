#pragma once
#include "./system.h"
#include "../memory/irq/irq.h"
#include "../gui/terminal.h"
void realclock_handler(struct regs *r){

}

void realclock_install()
{
  irq_install_handler(8, realclock_handler);
}