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

#ifndef xnix_io_h
#define xnix_io_h

#include "types.h"

#define RAMSCREEN 0xB8000
#define SIZESCREEN 0xFA0
#define SCREENLIM 0xB8FA0

namespace steel {

    class io {
    private:
        static char*	real_screen;
        static char	screen[SIZESCREEN];

        static char	inbuf[512];	/* console buffer */
        static int	keypos;	/* console read position */
        static int	inlock;	/* console state */
        static int	keystate;	/* console type keyboard */


        static char fcolor;	/* console foreground color */
        static char	bcolor;	/* console background color */
        static char	x;	/* console x position */
        static char	y;	/* console y position */
        static char kattr;	/* console attribut */
        static char*	vidmem;	/* screen video memory */

    public:

        enum Color {
            Black =0,
            Blue =1,
            Green =2,
            Cyan =3,
            Red =4,
            Magenta =5,
            Orange =6,
            LightGrey =7,
            DarkGrey =8,
            LightBlue =9,
            LightGreen =10,
            LightCyan =11,
            LightRed =12,
            LightMagenta=13,
            Yellow =14,
            White =15
        };

        /* io class functions **/
        /** output byte */
        static void outb(adr ad,u8 v);
        /** output word */
        static void outw(adr ad,u16 v);
        /** output word */
        static void outl(adr ad,u32 v);

        /** input byte */
        static u8	inb(adr ad);
        /** input word */
        static u16	inw(adr ad);
        /** input word */
        static u32	inl(adr ad);

        /** put a byte on the console */
        static void putctty(char c);

        /** read a string in the console */
        static u32 read(char* buf,u32 count);

        /** put a byte on screen */
        static void putc(char c);

        /** change colors */
        static void setColor(char fcol,char bcol);

        /** change cursor position */
        static void setXY(char xc,char yc);

        /** clear screen */
        static void clear();

        /** put a string in screen */
        static void print(const char *s, ...);

        /** x cursor position */
        static u32	getX();
        /** y cursor position */
        static u32	getY();

        /* change the io interface */
        static void switchtty();

        /* x86 functions */
        static void scrollup(unsigned int n);
        static void save_screen();
        static void load_screen();

        enum ConsoleType {
            BUFFERED,
            GETCHAR
        };
        
    };
    
}

#endif
