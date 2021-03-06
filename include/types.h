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

#ifndef STEEL_TYPES_H
#define STEEL_TYPES_H

namespace steel {
        typedef signed char int8_t;
        typedef signed short int int16_t;
        typedef signed int int32_t;
        typedef signed long long int64_t;
    
        typedef unsigned char uint8_t;
        typedef unsigned short int uint16_t;
        typedef unsigned int uint32_t;
        typedef unsigned long long uint64_t;
        
        typedef uint32_t uint;
        
        typedef uint64_t ptr_t;
        
        #ifndef __cplusplus
        typedef uint8_t bool;
        #endif
        #define true ((bool)1)
        #define false ((bool)0)
        #define yes ((bool)1)
        #define no ((bool)0)
        
        #define NULL ((void*)0)
}

#endif
