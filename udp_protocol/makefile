#upd/ip 
CC=gcc
CFLAGS= -pedantic  
LIBS = -lnsl -lsocket

OBJC = udpclient.o client.o serr.o copybyte.o sighand.o
OBJS = udpserver.o server.o serr.o copybyte.o gettime.o filecopy.o

all: udps udpc

udps: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o udps $(LIBS)
udpserver.o : inet.h
server.o :inet.h
serr.o : inet.h
copybyte : inet.h
filecopy.o : inet.h

udpc: $(OBJC)
	$(CC) $(CFLAGS) $(OBJC) -o udpc $(LIBS)
udpclient.o : inet.h
client.o : inet.h
serr.o :inet.h
copybyte.o : inet.h

clean: 
	@rm  -f *.o udps udpc



