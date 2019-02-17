CC=gcc
CFLAGS= -pedantic
LIBS = -lnsl -lsocket -lpthread -lthread

OBJC = client.o serr.o filesend.o
OBJS = serv.o serr.o slave.o authenticate.o getstatus.o

all: handin server

handin: $(OBJC)
	$(CC) $(FLAGS) $(OBJC) -o handin $(LIBS)
client.o : inet.h
serr.o : inet.h
filesend.o : inet.h

server: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o server $(LIBS)
serv.o : inet.h
serr.o : inet.h
slave.o : inet.h
authenticate.o : inet.h
getstatus.o : inet.h

clean:
	@rm -f *.o handin server
