CC=gcc
ASMBIN=nasm

all : asm cc link clean
asm : 
	$(ASMBIN) -f elf32 func.asm -o func.o
cc :
	$(CC) -m32 -c main.c -o main.o
link :
	$(CC) -m32 main.o func.o -o main -lm
clean :
	rm *.o
