#pragma once

#include "../../system/system.h"

struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;        /* Our kernel segment goes here! */
    unsigned char always0;     /* ALWAYS set to 0! */
    unsigned char flags;       /* Set using the above table! */
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idt_entry idt[256]; // 256 entries
struct idt_ptr _idtp;

extern void _idt_load();

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].always0 = 0;
    idt[num].sel = sel;
    idt[num].flags = flags;
}

void idt_install()
{
    /* Sets the special IDT pointer up, just like in 'gdt.c' */
    _idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    _idtp.base = &idt;

    /* Clear out the entire IDT, initializing it to zeros */
    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    /* Add any new ISRs to the IDT here using idt_set_gate */

    _idt_load();
}
