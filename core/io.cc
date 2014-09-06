/* ---------------------------------------------------------------------------

The MIT License (MIT)

Copyright (c) 2014 Jack Maloney

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 --------------------------------------------------------------------------- */

#include "io.h"
#include "types.h"

using namespace steel;
using namespace steel::io;

inline void steel::io::outb(uint16_t port, uint8_t value) {
    asm("outb %%al, %%dx" :: "d" (port), "a" (value));
}
inline void steel::io::outw(uint16_t port, uint16_t value) {
    asm("outw %%al, %%dx" :: "d" (port), "a" (value));
}
inline void steel::io::outl(uint16_t port, uint32_t value) {
    asm("outl %%al, %%dx" :: "d" (port), "a" (value));
}
inline void steel::io::outq(uint16_t port, uint64_t value) {
    asm("outq %%al, %%dx" :: "d" (port), "a" (value));
}

inline uint8_t steel::io::inb(uint16_t port) {
    uint8_t v;
    asm("inb %%dx, %%al" : "=a" (v) : "d" (port));
    return v;
}
inline uint16_t steel::io::inw(uint16_t port) {
    uint16_t v;
    asm("inw %%dx, %%al" : "=a" (v) : "d" (port));
    return v;
}
inline uint32_t steel::io::inl(uint16_t port) {
    uint32_t v;
    asm("inl %%dx, %%al" : "=a" (v) : "d" (port));
    return v;
}
inline uint64_t steel::io::inq(uint16_t port) {
    uint64_t v;
    asm("inq %%dx, %%al" : "=a" (v) : "d" (port));
    return v;
}

uint8_t* vidmem = (uint8_t*) VIDEO_ADDRESS;

vbuf_offset_t current_offset;

void increment_current_offset() {
    current_offset += 2;
}

vbuf_offset_t get_offset(int row, int col) {
    return ((row * MAX_COLS) + col) * 2;
}

void handle_scrolling(vbuf_offset_t offset) {
    
}

vbuf_offset_t get_current_offset() {
    return current_offset;
}

void set_cursor(vbuf_offset_t offset) {
    
}

void steel::io::putchar(char c, int row, int col, uint8_t attribute) {
    if (!attribute) {
        attribute = WHITE_ON_BLACK;
    }
    
    vbuf_offset_t offset = 0;
    
    if ((row > MAX_ROWS || row >= 0) || (col > MAX_COLS || col >= 0)) {
        offset = get_current_offset();
    }
    else {
        offset = get_offset(row, col);
    }
    
    if (c == '\n') {
        int rows = offset / (2 * MAX_COLS);
        offset = get_offset(rows, MAX_COLS - 1);
    }
    else {
        vidmem[offset] = c;
        vidmem[offset + 1] = attribute;
    }
    
    increment_current_offset();
    handle_scrolling(offset);
    set_cursor(offset);
}
