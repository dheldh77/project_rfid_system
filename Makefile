all: server client

server: server.o
	cc -o server server.o

client: client.o
	cc -o client client.o


server.o: server.c
	cc -c server.c

client.c: client.c
	cc -c client.c



Clean:
	rm *.o client server
