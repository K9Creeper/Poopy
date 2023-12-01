#pragma once
#include "../system.h"

#include "../../memory/irq/irq.h"

typedef void( * keyboard_input_handle_fn)(void);

struct Key {
  unsigned char key;
  bool pressed;
};

static struct Key keymap[128] = {
  {
    0,
    false
  },
  {
    27,
    false
  },
  {
    '1',
    false
  },
  {
    '2',
    false
  },
  {
    '3',
    false
  },
  {
    '4',
    false
  },
  {
    '5',
    false
  },
  {
    '6',
    false
  },
  {
    '7',
    false
  },
  {
    '8',
    false
  },
  /* 9 */ {
    '9',
    false
  },
  {
    '0',
    false
  },
  {
    '-',
    false
  },
  {
    '=',
    false
  },
  {
    '\b',
    false
  },
  /* Backspace */ {
    '\t',
    false
  },
  /* Tab */ {
    'q',
    false
  },
  {
    'w',
    false
  },
  {
    'e',
    false
  },
  {
    'r',
    false
  },
  /* 19 */ {
    't',
    false
  },
  {
    'y',
    false
  },
  {
    'u',
    false
  },
  {
    'i',
    false
  },
  {
    'o',
    false
  },
  {
    'p',
    false
  },
  {
    '[',
    false
  },
  {
    ']',
    false
  },
  {
    '\n',
    false
  },
  /* Enter key */ {
    0,
    false
  },
  /* 29   - Control */ {
    'a',
    false
  },
  {
    's',
    false
  },
  {
    'd',
    false
  },
  {
    'f',
    false
  },
  {
    'g',
    false
  },
  {
    'h',
    false
  },
  {
    'j',
    false
  },
  {
    'k',
    false
  },
  {
    'l',
    false
  },
  {
    ';',
    false
  },
  /* 39 */ {
    '\'',
    false
  },
  {
    '`',
    false
  },
  {
    0,
    false
  },
  /* Left shift */ {
    '\\',
    false
  },
  {
    'z',
    false
  },
  {
    'x',
    false
  },
  {
    'c',
    false
  },
  {
    'v',
    false
  },
  {
    'b',
    false
  },
  {
    'n',
    false
  },
  /* 49 */ {
    'm',
    false
  },
  {
    ',',
    false
  },
  {
    '.',
    false
  },
  {
    '/',
    false
  },
  {
    0,
    false
  },
  /* Right shift */ {
    '*',
    false
  },
  {
    0,
    false
  },
  /* Alt */ {
    ' ',
    false
  },
  /* Space bar */ {
    0,
    false
  },
  /* Caps lock */ {
    0,
    false
  },
  /* 59 - F1 key ... > */ {
    0,
    false
  },
  {
    0,
    false
  },
  {
    0,
    false
  },
  {
    0,
    false
  },
  {
    0,
    false
  },
  {
    0,
    false
  },
  {
    0,
    false
  },
  {
    0,
    false
  },
  {
    0,
    false
  },
  /* < ... F10 */ {
    0,
    false
  },
  /* 69 - Num lock*/ {
    0,
    false
  },
  /* Scroll Lock */ {
    0,
    false
  },
  /* Home key */ {
    0,
    false
  },
  /* Up Arrow */ {
    0,
    false
  },
  /* Page Up */ {
    '-',
    false
  },
  {
    0,
    false
  },
  /* Left Arrow */ {
    0,
    false
  },
  {
    0,
    false
  },
  /* Right Arrow */ {
    '+',
    false
  },
  {
    0,
    false
  },
  /* 79 - End key*/ {
    0,
    false
  },
  /* Down Arrow */ {
    0,
    false
  },
  /* Page Down */ {
    0,
    false
  },
  /* Insert Key */ {
    0,
    false
  },
  /* Delete Key */ {
    0,
    false
  },
  {
    0,
    false
  },
  {
    0,
    false
  },
  {
    0,
    false
  },
  /* F11 Key */ {
    0,
    false
  },
  /* F12 Key */ {
    0,
    false
  } /* All other keys are undefined */
};
static unsigned char last_scancode = -1;

static void * keyboard_input_handles[64];

bool add_to_keyboard_input_handles(void * v) {
  for (int i = 0; i < 64; i++)
    if (!keyboard_input_handles[i]) {
      keyboard_input_handles[i] = v;
      return true;
    }
  return false;
}

bool remove_from_keyboard_input_handles(void * v) {
  for (int i = 0; i < 64; i++) {
    if (!keyboard_input_handles[i])
      continue;
    if (v == keyboard_input_handles[i]) {
      keyboard_input_handles[i] = (void * ) 0;
      return true;
    }
  }
  return false;
}

void keyboard_handler(struct regs * r) {
  /* keyboard's data buffer */
  const unsigned char scancode = inportb(0x60);
  last_scancode = scancode;

  if (scancode <= 80 && scancode)
    keymap[scancode].pressed = true;
  else if ((scancode - 0x80) > 0) // no out of bounds
    keymap[scancode - 0x80].pressed = false; // released

  // run
  for (int i = 0; i < 64; i++) {
    if (!keyboard_input_handles[i])
      continue;
    ((keyboard_input_handle_fn) keyboard_input_handles[i])();
  }
}

void keyboard_install() {
  irq_install_handler(1, keyboard_handler); /* IRQ1 */
}