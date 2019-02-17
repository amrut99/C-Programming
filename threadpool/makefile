#tcp/ip server-client using BSD

CC = gcc
CFLAGS = -pedantic -ansi 
OBJC = tcpclient.o client.o serr.o
OBJS = tcpserver.o server.o serr.o

all: server client servpool

server: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o server -lnsl -lsocket
tcpserver.o:inet.h
server.o: inet.h
serr.o:inet.h

client: $(OBJC)
	$(CC) $(CFLAGS) $(OBJC) -o client -lnsl -lsocket
tcpclient.o:inet.h
client.o:inet.h
serr.o:inet.h

clean: 
	@rm -f *.o tcps tcpc

print:
	pr tcpserver.c serr.c server.c tcpclient.c client.c  makefile  \
inet.h | lpr -Pcenter1

