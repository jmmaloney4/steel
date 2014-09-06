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

#ifndef STEEL_IO_H
#define STEEL_IO_H

#include "types.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

// Attribute byte for our default colour scheme.
#define WHITE_ON_BLACK 0x0f

//Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

namespace steel {
	namespace io {
        
        typedef uint16_t vbuf_offset_t;
        
        void outb(uint16_t port, uint8_t value);
        void outw(uint16_t port, uint16_t value);
        void outl(uint16_t port, uint32_t value);
        void outq(uint16_t port, uint64_t value);
        
        uint8_t inb(uint16_t port);
        uint16_t inw(uint16_t port);
        uint32_t inl(uint16_t port);
        uint64_t inq(uint16_t port);
        
        void putchar(char c, int row, int col, uint8_t attribute);
    }
}

#endif
