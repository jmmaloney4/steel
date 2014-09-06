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

extern "C"
{
    int __cxa_atexit(void (*Destructor) (void *), void *Parameter, void *HomeDSO);
    void __cxa_finalize(void *);
    void __cxa_pure_virtual();
    void __stack_chk_guard_setup();
    void __attribute__((noreturn)) __stack_chk_fail();
    void _Unwind_Resume();
}

void *__dso_handle;	
void *__stack_chk_guard(0);
namespace __cxxabiv1 {
    __extension__ typedef int __guard __attribute__((mode(__DI__)));
    extern "C" {
        int __cxa_guard_acquire(__guard *Guard)	{ return ! *(char *) (Guard); }
        void __cxa_guard_release(__guard *Guard)	{ *(char *) Guard = 1; }
        void __cxa_guard_abort(__guard *)	{ }
    }
}

int __cxa_atexit(void (*) (void *), void *, void *) {
    return 0;
}

void _Unwind_Resume(){
}

void __cxa_finalize(void *) {
}
void __cxa_pure_virtual() {
}
void __stack_chk_guard_setup() {
{
    unsigned char *Guard;
    Guard = (unsigned char *) &__stack_chk_guard;
    Guard[sizeof(__stack_chk_guard) - 1] = 255;
    Guard[sizeof(__stack_chk_guard) - 2] = '\n';
    Guard[0] = 0;
}
struct IntRegs;
void __attribute__((noreturn)) __stack_chk_fail() {
    while (true) {}
}
void operator delete(void *ptr)
{
    kfree(ptr);
}

#ifndef __arm__

void* operator new(size_t len) {
    return (void*)kmalloc(len);
}

void operator delete[](void *ptr) {
    ::operator delete(ptr);
}

void* operator new[](size_t len) {
    return ::operator new(len);
}

#else
void* operator new(size_t len) {
    return (void*)kmalloc(len);
}

void operator delete[](void *ptr) {
    ::operator delete(ptr);
}
void* operator new[](size_t len) {
    return ::operator new(len);
}
#endif

void *__gxx_personality_v0=(void*)0xDEADBEAF;
