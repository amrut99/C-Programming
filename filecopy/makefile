#first make file example

CC = gcc
CFLAGS = -c
LIBS = -lm
OBJS = main.o checkargs.o checkncreatdest.o copydsrc2dest.o \
copyfsrc2dest.o printstats.o

target : $(OBJS)
	gcc -o target $(OBJS)

main.o : main.c 
	gcc -c main.c
checkargs.o : checkargs.c 
	gcc -c checkargs.c
checkncreatdest.o : checkncreatdest.c
	gcc -c checkncreatdest.c
copydsrc2dest.o : copydsrc2dest.c
	gcc -c copydsrc2dest.c
copyfsrc2dest.o : copyfsrc2dest.c
	gcc -c copyfsrc2dest.c
printstats.o : printstats.c
	gcc -c printstats.c
clean : 
	rm target $(OBJS)
