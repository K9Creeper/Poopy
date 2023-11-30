#pragma once
#include <stdbool.h>
#include "../../system/system.h"
#include "../terminal.h"

typedef void (*callablefn)(void);

struct cmdcommandarguement{
const char* symb;
int value; // just base it off if value
};

struct cmdcommand{
const char* in;
struct cmdcommandarguement arguements[16];
void* fn;
};

struct cmdcommand cmdcommands[1]= {
{ "clear", {}, (void*)&terminal_clear }
};

bool cmd_command_equals(const char* str1, const char* str2)
{
  for(int i = 0; i < min(strlen(str1), strlen(str2)); i++)
    {
      const char c1 = str1[i];
      const char c2 = str2[i];
      if(c1 == ' ')
        break;
      if(c1 != c2){
        if(isletter(c1) && isletter(c2))
          {
            if(islower(c1) && !islower(c2) && (c1-32 != c2))
                return false;
          }
          else
            return false;
        }
    }
  return true;
}

struct cmdcommand* get_cmd_command(const char* in)
{
  for(int i = 0 ; i < (sizeof(cmdcommands)/sizeof(struct cmdcommand)); i++)
    {
      if(strlen(in) > 0 && cmd_command_equals(cmdcommands[i].in, in))
        return &cmdcommands[i];
    }
  return (struct cmdcommand*)0;
}