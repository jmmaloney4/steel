ARCH=x86

include ./kernel/Makefile
include ./core/Makefile
include ./arch/$(ARCH)/Makefile

CC=clang
CXX=clang

CFLAGS=-std=c11 -I ./ -I ./include/ -arch x86_64
CXXFLAGS=-std=c++11 -I ./ -I ./include/ -arch x86_64

LD=ld

ASM=nasm
ASMFLAGS=-f macho64

BIN_DIR=$(pwd)/build

all: steel
	@echo "Done"

steel: $(OBJS)
	$(LD) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ -c $<
	
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.s
	$(ASM) $(ASMFLAGS) -o $@ $<

clean:
	rm $(OBJS)
