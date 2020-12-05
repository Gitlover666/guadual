CC = gcc
CFLAGS =-O0 -g -Wall

test:test.c linkqueue.c 
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm -rf test
	