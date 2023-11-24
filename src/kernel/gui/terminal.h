#pragma once

#define VGA_COLOR_GREEN 2
#define VGA_COLOR_BLACK 0
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#include "../includes.h"

struct Terminal{
bool initalized;
size_t row;
size_t column;
uint8_t color;
uint16_t* buffer;
}terminal;

void terminal_update_cursor(uint16_t x, uint16_t y) {
  uint16_t pos = y * VGA_WIDTH + x; outportb(0x3D4, 0x0F); outportb(0x3D5, (uint8_t) (pos & 0xFF)); outportb(0x3D4, 0x0E); outportb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF)); }

static inline uint8_t terminal_vga_entry_color( uint16_t fg, uint16_t bg) { return fg | bg << 4; }

static inline uint16_t terminal_vga_entry(unsigned char uc, uint8_t color) { return (uint16_t) uc | (uint16_t) color << 8; }

void terminal_init(void) {
terminal.initalized = true;
  terminal.row = 0;
  terminal.column = 0;
  terminal.color = terminal_vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
  terminal.buffer = (uint16_t*) 0xB8000;
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      terminal.buffer[index] = terminal_vga_entry(' ', terminal.color);
    }
  }
}

void terminal_set_color(uint8_t color) { terminal.color = color; }

void terminal_put_entry_at(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;
  terminal.buffer[index] = terminal_vga_entry(c, color);
}

void terminal_put_char(char c) {
  if(c == '\n'){
    terminal.column = 0;
    terminal.row++;
  }
  terminal_put_entry_at(c, terminal.color, terminal.column, terminal.row);
  if (++terminal.column == VGA_WIDTH) {
    terminal.column = 0;
    if (++terminal.row == VGA_HEIGHT)
      terminal.row = 0;
  }
}

void terminal_remove_last_char() {
  terminal.column--;
  terminal_put_entry_at(' ', terminal.color, terminal.column, terminal.row);
  if (terminal.column == VGA_WIDTH) {
    terminal.column = 0;
    if (terminal.row == VGA_HEIGHT)
      terminal.row = 0;
  }
  terminal_update_cursor(terminal.column, terminal.row);
}

void terminal_write(const char* data, size_t size)  {
  for (size_t i = 0; i < size; i++){
      terminal_put_char(data[i]);
  }
  terminal_update_cursor(terminal.column, terminal.row);
}

void terminal_write_string(const char* data) {
  terminal_write(data, strlen(data));
}