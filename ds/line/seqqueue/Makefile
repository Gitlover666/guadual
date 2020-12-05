CC = gcc
CFLAGS =-O0 -g -Wall

test:test.c seqqueue.c 
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm -rf test
	