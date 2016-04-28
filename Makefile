CC	:= gcc

bns: bns.c
	$(CC) -o $@ $<

.PHONY: clean
clean: bns
	rm -fr $<
