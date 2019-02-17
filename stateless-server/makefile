# rpc 
BIN = stateless_svc copyrpc
CC = gcc
GEN = stateless_clnt.c stateless_svc.c stateless.h stateless_xdr.c
LIB = -lnsl
RPCCOM = rpcgen
CFLAGS = -DDEBUG

all: $(BIN)

$(GEN): stateless.x
	$(RPCCOM) stateless.x

stateless_svc: stateless_svc.o stateless_proc.o stateless_xdr.o
	$(CC) stateless_svc.o stateless_proc.o stateless_xdr.o \
	-o stateless_svc $(LIB)

copyrpc: copyrpc.o stateless_clnt.o stateless_xdr.o
	$(CC) copyrpc.o stateless_clnt.o stateless_xdr.o \
	-o copyrpc $(LIB)

copyrpc.o: stateless.h

stateless_svc.o: stateless.h

clean: 
	@rm -f $(GEN) *.o $(BIN) 
