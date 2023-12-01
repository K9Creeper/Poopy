#pragma once
#include <stdbool.h>

#include "../../system/system.h"

#include "../terminal.h"

typedef void( * callablefn)(void);

struct cmdcommandarguement {
  const char * symb;
  int value; // just base it off if value
};

struct cmdcommand {
  const char * in;
  struct cmdcommandarguement arguements[16];
  void * fn;
};

void list_cmdcommands();

struct cmdcommand cmdcommands[2] = {
  {
    "clear",
    {},
    (void * ) & terminal_clear
  },
  {
    "help",
    {},
    (void * ) & list_cmdcommands
  }
};

void list_cmdcommands() {
  terminal_write_string("\n-- LIST OF COMMANDS --\n");
  for (int i = 0; i < sizeof(cmdcommands) / sizeof(struct cmdcommand); i++) {
    terminal_write_string(" -  ");
    terminal_write_string(cmdcommands[i].in);
    terminal_write_string("\n");
  }
  terminal_write_string("-- END OF COMMANDS--\n\n");
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