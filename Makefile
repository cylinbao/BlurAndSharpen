CC	:= gcc
CFLAGS	:=

bns: bns.c bmp.h
	$(CC) -o $@ $(CFLAGS) $<

.PHONY: clean
clean: bns Output/*
	rm -fr $?
