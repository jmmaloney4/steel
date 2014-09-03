ASM=nasm
CC=clang
CXX=clang
LD=ld

ASMFLAGS= -f elf64
UFLAGS= -ffreestanding -I ./ -I ./include/
CFLAGS= $(UFLAGS)
CXXFLAGS= $(UFLAGS)

all: steel

include boot/Makefile
include kernel/Makefile
include core/Makefile

steel: boot/boot.bin kernel.bin
	cat boot/boot.bin kernel.bin > steel	

kernel.bin: $(OBJS)
	$(LD) --oformat=binary $(OBJS) -o ./kernel.bin

%.o: %.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm $(OBJS) boot/boot.bin kernel.bin steel

run: steel
	qemu-system-x86_64 steel
