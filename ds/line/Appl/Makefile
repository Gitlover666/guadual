CC = gcc
CFLAGS =-O0 -g -Wall

test:test.c Alinklist.c 
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm -rf test
	