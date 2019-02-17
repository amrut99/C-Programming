#include "inet.h"

void serverpid(int pipe_fd[2]){
	int n,fd,sockfd;
	char line[MAXLINE],buf[MAXLINE];
	void gettime(char *);
  while(1){
	
     if((n=read(pipe_fd[0],line,MAXLINE))>0){
	
/*	n=strlen(line);
        line[n] = '\0';
	
	sockfd=atoi(line);
	printf("socket :%d",sockfd);
	if((n=read(sockfd,line,MAXLINE))<0)
                serr("serverpool: read socket failed");*/

        line[n] = '\0';
	if((fd=open(line,O_RDONLY))<0)
	  serr("serverpid: open  file failed");

	while((n=read(fd,buf,MAXLINE))>0){
	   if(write(1,buf,n)!=n){
	     serr("tcpserver: writing file.");
	   }
	}
	
     close(fd);
     }
   n=0;
  }
}
