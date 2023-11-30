#pragma once
#include "../../system/input/keyboard.h"
#include "../terminal.h"
#include "./cmdcommands.h"

#define CMD_BUFFER_SIZE 64

struct cmd_inputs {
  char buffer[CMD_BUFFER_SIZE];
  int curr;
} cmd_input_buffer;

enum cmd_states { idle = 0, printing } cmd_state;

void cmd_print_dir() {
  cmd_state = printing;
  terminal_write_string("kernel> ");
  cmd_state = idle;
}

void clear_cmd_input_buffer() {
  for (int ret = 0; ret < CMD_BUFFER_SIZE; ret++)
    cmd_input_buffer.buffer[ret] = '\0';  // set everything to nothing
  cmd_input_buffer.curr = 0;
}

bool cmd_run_command() {
  // next line
  {
    terminal.row++;
    terminal.column = 0;
  }

  void* fn = (void*)0;

  // get func
  {
    struct cmdcommand* c = get_cmd_command(cmd_input_buffer.buffer);
    clear_cmd_input_buffer();
    if (c != (struct cmdcommand*)0) fn = c->fn;
  }
  
  // call
  {
    if (fn == (void*)0) {
      terminal_write_string("[INVALID COMMAND]");
      terminal.row++;
      terminal.column = 0;
    } else {
      ((callablefn)fn)();
      // call
    }
  }
  clear_cmd_input_buffer(); // make sure cleared!
  cmd_print_dir();
  return (fn == (void*)0);  // success?
}

void cmd_input() {
  unsigned char key = keymap[last_scancode].key;
  if (cmd_state != idle) clear_cmd_input_buffer();
  if (key != '\n') {
    if (key == '\b') {
      if (cmd_input_buffer.curr > 0) {
        terminal_remove_last_char();
        cmd_input_buffer.buffer[cmd_input_buffer.curr - 1] = '\0';
        cmd_input_buffer.curr--;
      }
    } else if (ispunct(key) || isletter(key) || isdigit(key) || key == ' ' ||
               key == '=' || key == '@') {
      // create control-key(s) support using keymap[x]
      {
        // shift
        if (keymap[42].pressed || keymap[54].pressed) {
          if (key <= 'z' && key >= 'A') {
            key -= 32;  // uppercase
          } else if (isdigit(key)) {
            const int num = key - 48;
            switch (num) {
              case 0:
                key = ')';
                break;
              case 1:
                key = '!';
                break;
              case 2: {
                key = '@';
                break;
              }
              case 3:
                key = '#';
                break;
              case 4:
                key = '$';
                break;
              case 5:
                key = '%';
                break;
              case 6:
                key = '^';
                break;
              case 7:
                key = '&';
                break;
              case 8:
                key = '*';
                break;
              case 9:
                key = '(';
                break;
            }
          }

          if (key == '=') {
            if (!keymap[27].pressed)
              key = '+';
            else
              key = '}';
          } else if (key == '.')
            key = '>';
          else if (key == ',')
            key = '<';
          else if (key == '<')
            key = '|';
          else if (key == '/')
            key = '?';
          else if (key == '-')
            key = '_';
          else if (key == '@' && !keymap[3].pressed)
            key = '~';
          else if (key == '\'')
            key = '"';
          else if (key == ';') {
            if (!keymap[26].pressed)
              key = ':';
            else
              key = '{';
          }
        }
      }

      // show to console buffer and cmd buffer
      {
        if (cmd_input_buffer.curr < CMD_BUFFER_SIZE - 1) {
          cmd_input_buffer.buffer[cmd_input_buffer.curr] = key;
          cmd_input_buffer.curr++;
          terminal_put_char(key);
          terminal_update_cursor(terminal.column, terminal.row);
        }
      }
    }
  } else
    cmd_run_command();
}

void cmd_install_keyboard() {
  add_to_keyboard_input_handles(&cmd_input);
  cmd_print_dir();
}