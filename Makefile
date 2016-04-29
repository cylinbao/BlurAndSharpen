TARGET	= bns-riscv
TARGET-HOST	= bns
CC	= ../riscv/bin/riscv64-unknown-elf-gcc
FLAGS	= -g -O2
CC-HOST	= gcc
SPIKE	= ../riscv/bin/spike
SPIKE-OPTION	= --dc=32:2:64 pk

bns: bns.c bmp.h
	$(CC) -o $(TARGET) $(FLAGS) $<

.PHONY: clean host run run-host

clean:
	rm -fr $(TARGET) $(TARGET-HOST) ./Output/*

host: bns.c bmp.h
	$(CC-HOST) -o $(TARGET-HOST) $(FLAGS) $<

run: 
	$(SPIKE) $(SPIKE-OPTION) $(TARGET)

run-host: 
	./$(TARGET-HOST)
