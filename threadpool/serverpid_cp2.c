#include "inet.h"

void serverpid(int pipe_fd[2],int listenfd){
	int n,fd,sockfd;
	char line[MAXLINE],buf[MAXLINE],sockadd[MAXLINE];
	ssize_t x; 
	void gettime(char *);
  while(1){
	
     if((n=read(pipe_fd[0],line,MAXLINE))>0){
	
        line[n] = '\0';
	
     if((n=read(pipe_fd[0],sockadd,MAXLINE))==0){
	 serr("\nserverpid: pipe read ");
     }
	sockadd[n]='\0';
	sockfd=atoi(sockadd);
	printf("serverpid :socket :%d",sockfd);
/*	if((n=read(sockfd,line,MAXLINE))<0)
                serr("\nserverpool: read socket failed");

        line[n] = '\0';*/
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
