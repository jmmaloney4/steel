ARCH=x86_64

include ./kernel/Makefile
include ./core/Makefile
include ./boot/Makefile

CC=clang
CXX=clang

CFLAGS=-std=c11 -I ./ -I ./include/ -arch x86_64 -nostdlib -ffreestanding
CXXFLAGS=-std=c++11 -I ./ -I ./include/ -arch x86_64 -nostdlib -ffreestanding

LD=ld
LDFLAGS=-e start

ASM=nasm
ASMFLAGS=-f macho64

BIN_DIR=$(pwd)/build

all: steel

steel: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ -c $<
	
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

clean:
	rm $(OBJS)
