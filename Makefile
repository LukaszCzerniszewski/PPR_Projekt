CFLAGS = -O2 -Wall
LDFLAGS = -s
CC = gcc
LD = ld
MAKE = make



SERVER_CFLAGS=`xmlrpc-c-config  abyss-server --cflags`
SERVER_LDFLAGS=`xmlrpc-c-config abyss-server --libs`
CLIENT_CFLAGS=`xmlrpc-c-config  libwww-client --cflags`
CLIENT_LDFLAGS=`xmlrpc-c-config libwww-client --libs`

all: proces2


proces2: Proces2.c
	$(CC) $(SERVER_CFLAGS)$(CLIENT_CFLAGS)	$(CFLAGS)  -c $<
	$(CC) $(SERVER_LDFLAGS)$(CLIENT_LDFLAGS)	$(LDFLAGS) $< -o $@
	

clean:
	rm Proces2.o
	rm client.o

