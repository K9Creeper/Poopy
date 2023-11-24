#pragma once
#include <stdbool.h>

typedef unsigned int size_t;

unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count){
  unsigned char *csrc = (unsigned char *)src;  
  unsigned char *cdest = (unsigned char *)dest;  

  // Copy contents of src[] to dest[]  
  for (int i=0; i<count; i++)  
      cdest[i] = csrc[i];  
  return cdest;
}

unsigned char *memset(unsigned char *dest, unsigned char val, int count){
  register unsigned char *ptr = (unsigned char*)dest;
  while (count-- > 0)
    *ptr++ = val;
  return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count){
register unsigned short *ptr = (unsigned short*)dest;
while (count-- > 0)
  *ptr++ = val;
return dest;
}

int strlen(const char *str){ size_t len = 0; while (str[len]) len++;  return len; }

unsigned char inportb (unsigned short _port){
    unsigned char rv;
    asm volatile ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data){
    asm volatile("outb %1, %0" : : "dN" (_port), "a" (_data));
}

bool ispunct(const char c)
{
  return (c == '!' || c == '"' || c == '#' || c == '$' || c == '%' || c == '&' || c == '\''|| c == '(' || c == ')' || c == '*' || c == '+' || c == ',' || c == '-' || c == '.' || c == '/' || c == ':' || c == ';' || c == '?' || c == '@' || c == '[' || c == '\\' || c == ']' || c == '^' || c == '_' || c == '`' || c == '{' || c == '|' || c == '}' || c ==  '~' );
}

bool isletter(const char c)
{
  return (c >= 'A' && c <= 'z');
}

bool isdigit(const char c)
{
  return (c >= '0' && c <= '9');
}