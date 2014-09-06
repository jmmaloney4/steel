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

#include "types.h"

namespace steel {
    namespace gdt {
        
        struct gdt_descriptor {
            uint16_t limit;
            uint64_t base;
        } __attribute__((packed));
        
        struct segment_descriptor {
            uint64_t limit15_0:16;
            uint64_t base23_0:24;
            uint64_t type:4;
            uint64_t S:1;
            uint64_t DPL:2;         /* descriptor priority level */
            uint64_t P:1;           /* present */
            uint64_t limit19_16:4;
            uint64_t AVL:1;         /* available for system use*/
            uint64_t L:1;           /* long mode */
            uint64_t D_B:1;         /* operation size */
            uint64_t G:1;           /* granularity*/
            uint64_t base31_24:40;
            uint64_t pad:32;
        } __attribute__((packed));
        
        typedef gdt_descriptor gdtptr_t;
        typedef segment_descriptor gdtdes_t;
        
    }
}
