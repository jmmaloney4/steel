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

 ---------------------------------------------------------------------------- */

#include "io.h"

using namespace steel;

char* steel::io::vidmem = (char*)RAMSCREEN;

char* steel::io::real_screen = (char*)RAMSCREEN;

inline void steel::io::outb(adr ad,u8 v) {
    asm("outb %%al, %%dx" :: "d" (ad), "a" (v));
}

inline void steel::io::outw(adr ad, u16 v) {
    asm("outw %%ax, %%dx" :: "d" (ad), "a" (v));
}

inline void steel::io::outl(adr ad, u32 v) {
    asm("outw %%eax, %%dx" :: "d" (ad), "a" (v));
}

inline void steel::io::outq(adr ad, u64 v) {
    asm("outq %%rax, %%dx" :: "d"(ad), "a"(v));
}

inline u8 steel::io::inb(adr ad) {
    u8 v;
    asm("inb %%dx, %%al" : "=a" (v) : "d" (ad));
    return v;
}

inline u16 steel::io::inw(adr ad) {
    u16 v;
    asm("inw %%dx, %%al" : "=a" (v) : "d" (ad));
    return v;
}

inline u32 steel::io::inl(adr ad) {
    u32 v;
    asm("inl %%dx, %%al" : "=a" (v) : "d" (ad));
    return v;
}

inline u64 steel::io::inq(adr ad) {
    u64 v;
    asm("inq %%dx, %%al" : "=a" (v) : "d" (ad));
    return v;
}
