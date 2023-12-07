#pragma once
#include <stdbool.h>

#include "../../system/system.h"

#include "../terminal.h"

typedef void( * callablefn)(void);

struct cmdcommand {
  const char * in;
  char arguements[4];
  void * fn;
};

void list_cmdcommands();
void cmd_test(const char* in);
struct cmdcommand cmdcommands[3] = {
  {
    "clear",
    { 0, 0, 0, 0 },
    (void * ) & terminal_clear
  },
  {
    "help",
    { 0, 0, 0, 0 },
    (void * ) & list_cmdcommands
  },
  {
    "test",
    { 'H', 0, 0, 0 },
    (void * ) &cmd_test
  }
};

void cmd_test(const char* in){
  terminal_write_string(in);
}

void list_cmdcommands() {
  terminal_write_string("\n-- LIST OF COMMANDS --\n");
  for (int i = 0; i < sizeof(cmdcommands) / sizeof(struct cmdcommand); i++) {
    terminal_write_string(" -  ");
    terminal_write_string(cmdcommands[i].in);
    terminal_write_string("\n");
  }
  terminal_write_string("-- END OF COMMANDS--\n\n");
}

char get_cmd_command_params(int index, const char* in)
{
  for (int i = index; i < strlen(in)-1; i++)
    {
      if (in[i] == '-')
        if(in[i+1] == isletter(in[i+1])){
          return in[i+1];
        }
    }
  return 0;
}

bool cmd_command_equals(const char * str1,
  const char * str2) {
  bool ret = false;
  for (int i = 0; i < strlen(str1); i++) {
    if (strlen(str2) != strlen(str1))
      return false;
    const char c1 = str1[i];
    const char c2 = str2[i];
    if (c1 == ' ')
      break;
    ret = true;
    if (c1 != c2) {
      if (isletter(c1) && isletter(c2)) {
        if (islower(c1) && !islower(c2)) {
          if (c1 - 32 == c2)
            continue;
        } else if (!islower(c1) && islower(c2)) {
          if (c1 == c2 - 32)
            continue;
        }
      }
      return false;
    }
  }
  return ret;
}

struct cmdcommand * get_cmd_command(const char * in) {
  for (int i = 0; i < (sizeof(cmdcommands) / sizeof(struct cmdcommand)); i++) {
    if (strlen(in) > 1 && cmd_command_equals(cmdcommands[i].in, in))
      return & cmdcommands[i];
  }
  return (struct cmdcommand * ) 0;
}