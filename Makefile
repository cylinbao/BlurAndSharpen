CC	:= gcc
CFLAGS	:= 

bns: bns.c
	$(CC) -o $@ $(CFLAGS) $<

.PHONY: clean
clean: bns Output/*
	rm -fr $?
