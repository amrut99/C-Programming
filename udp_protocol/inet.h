#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<signal.h>

#define MAXLINE 5004
#define MAXSZ 128
#define ACKSIZE 4
typedef struct sockaddr SA;

