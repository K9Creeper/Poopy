#pragma once
#include "./terminal.h"
#include "../system/input/keyboard.h"

struct cmd_inputs{
char buffer[64];
int curr;
}cmd_input_buffer;

enum cmd_states{
 idle = 0,
 printing
} cmd_state;

void cmd_print_dir()
{
  cmd_state = printing;
  terminal_write_string("kernel> ");
  cmd_state = idle;
}

void clear_cmd_input_buffer(){
  for(int ret = 0; ret < 64; ret++)
    cmd_input_buffer.buffer[ret] = '\0';
  cmd_input_buffer.curr = 0;
}

bool cmd_run_command(){
  // check if valid command
  // then execute that command that is relative to that
  {
  terminal.row++;
    terminal.column = 0;
  clear_cmd_input_buffer();
  cmd_print_dir();
  return true;
  }
}

void cmd_input(){
  char key = keymap[last_scancode].key;
  if(cmd_state != idle)
    clear_cmd_input_buffer();
  if(key != '\n'){
    if(key == '\b')
    {
      if(cmd_input_buffer.curr > 0){
        terminal_remove_last_char();
        cmd_input_buffer.buffer[cmd_input_buffer.curr-1] = '\0';
        cmd_input_buffer.curr--;
      }
    }
    else if(ispunct(key) || isletter(key) || isdigit(key) || key == ' '){

    // create control-key(s) support using keymap[x]
      
      if(cmd_input_buffer.curr < 64 - 1){
        cmd_input_buffer.buffer[cmd_input_buffer.curr] = key;
        cmd_input_buffer.curr++;
      terminal_put_char(key);
      terminal_update_cursor(terminal.column, terminal.row);
      }
    }
  }
  else
    cmd_run_command();
}

void cmd_install_keyboard()
{
  add_to_keyboard_input_handles(&cmd_input);
}