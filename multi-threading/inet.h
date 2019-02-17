#define _REENTRANT    
#include<errno.h>
#include<pthread.h>
#include<thread.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<signal.h>
#include<netdb.h>

#define MAXLINE 5000
#define QLEN 5
#define LOGINLEN 16
#define MAX_THREADS 5
typedef struct sockaddr SA;
int month,day,year;
