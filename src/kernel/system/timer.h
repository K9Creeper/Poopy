#pragma once

// 18 clocks ~= 1 second
#define CLOCK_TO_SECONDS 18 
#define CLOCK_TO_MILLISECONDS 18*.001

#include "../memory/irq/irq.h"
#include "../gui/terminal.h"

static int timer_ticks = 0;

bool has_seconds_passed(const int seconds, const int last_stick)
{
  return ((timer_ticks-last_stick) % (seconds*CLOCK_TO_SECONDS) == 0);
}

void timer_handler(struct regs *r)
{ 
  timer_ticks++;
  {
    
  }
}

void timer_install()
{ irq_install_handler(0, timer_handler); /* IRQ0 */ }