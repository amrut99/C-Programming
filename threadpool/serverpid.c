#include "inet.h"

void serverpid(int pipe_fd[2],int listenfd){
	int n,fd,sockfd;
	char line[MAXLINE],buf[MAXLINE],sockadd[MAXLINE];
	ssize_t x; 
  while(1){
	
     if((n=read(pipe_fd[0],sockadd,MAXLINE))>0){
	
        line[n] = '\0';
	
	sockfd=atoi(sockadd);

	printf("\nserverpid :socket :%d",sockfd);
	
	if((n=read(4,line,MAXLINE))<0)
                serr("\nserverpool: read socket failed");
        line[n] = '\0';
	printf("\nfile name:%s",line);

	if((fd=open(line,O_RDONLY))<0)
	  serr("\nserverpid: open  file failed");

	while((n=read(fd,buf,MAXLINE))>0){
	   if(write(1,buf,n)!=n){
	     serr("\ntcpserver: writing file. 1");
	   }
	   if(write(sockfd,buf,n)!=n){
	     serr("\ntcpserver: writing file. 2");
	   }

	}
    if(close(listenfd)<0) serr("tcpserver: socket close.");	
	printf("\ndone with loop.......");
     close(fd);

     }
   n=0;
   
  }
}
