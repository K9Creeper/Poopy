#pragma once
#include <stdbool.h>

typedef unsigned int size_t;

unsigned char * memcpy(unsigned char * dest,
  const unsigned char * src, int count) {
  unsigned char * csrc = (unsigned char * ) src;
  unsigned char * cdest = (unsigned char * ) dest;

  // Copy contents of src[] to dest[]  
  for (int i = 0; i < count; i++)
    cdest[i] = csrc[i];
  return cdest;
}

unsigned char * memset(unsigned char * dest, unsigned char val, int count) {
  register unsigned char * ptr = (unsigned char * ) dest;
  while (count--> 0)
    *
    ptr++ = val;
  return dest;
}

unsigned short * memsetw(unsigned short * dest, unsigned short val, int count) {
  register unsigned short * ptr = (unsigned short * ) dest;
  while (count--> 0)
    *
    ptr++ = val;
  return dest;
}

int strlen(const char * str) {
  size_t len = 0;
  while (str[len]) len++;
  return len;
}

int min(const int i1,
  const int i2) {
  if (i1 < i2) return i1;
  if (i1 > i2) return i2;
  return i1;
}

int find(const char * str,
  const char * f) {
  int ret = -1;
  for (int i = 0; i < strlen(str) - strlen(f); i++)
    for (int j = 0; i < strlen(f); j++) {
      if (str[i + j] != f[j]) {
        ret = -1;
        break;
      } else
        ret = i;
    }
  return ret;
}

unsigned char inportb(unsigned short _port) {
  unsigned char rv;
  asm volatile("inb %1, %0": "=a"(rv): "dN"(_port));
  return rv;
}

void outportb(unsigned short _port, unsigned char _data) {
  asm volatile("outb %1, %0":: "dN"(_port), "a"(_data));
}

bool ispunct(const char c) {
  return (c == '!' || c == '"' || c == '#' || c == '$' || c == '%' || c == '&' || c == '\'' || c == '(' || c == ')' || c == '*' || c == '+' || c == ',' || c == '-' || c == '.' || c == '/' || c == ':' || c == ';' || c == '?' || c == '@' || c == '[' || c == '\\' || c == ']' || c == '^' || c == '_' || c == '`' || c == '{' || c == '|' || c == '}' || c == '~');
}

bool isletter(const char c) {
  return (c >= 'A' && c <= 'z');
}
bool islower(const char c) {
  return (c >= 'a' && c <= 'z');
}
bool isdigit(const char c) {
  return (c >= '0' && c <= '9');
}