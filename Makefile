CC=gcc
CFLAGS=-I.
DEPS = server.h client.h
SERVER_OBJ = server.o main.o
CLIENT_OBJ = client.o server.o

all: server client

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(SERVER_OBJ)
	$(CC) -o $@ $^ $(CLFAGS)

client: $(CLIENT_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o

.PHONY: all clean