CC = gcc
CFLAGS =-O0 -g -Wall

test:test.c linkstack.c 
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm -rf test
	