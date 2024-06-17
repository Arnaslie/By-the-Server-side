CC=gcc
CFLAGS=-I.
DEPS = server.h
OBJ = server.o main.o

all: server client

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ)
	$(CC) -o $@ $^ $(CLFAGS)

client: client.o server.o
	$(CC) -o client client.o server.o

clean:
	rm -f *.o

.PHONY: all clean