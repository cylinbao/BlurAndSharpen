CC	:= gcc
CFLAGS	:= -g

bns: bns.c bmp.h
	$(CC) -o $@ $(CFLAGS) $<

.PHONY: clean
clean: bns Output/*
	rm -fr $?
