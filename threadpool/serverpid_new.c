#include "inet.h"

void serverpid(int pipe_fd[2]){
	int n,fd,sockfd;
	char line[MAXLINE],buf[MAXLINE],filename[MAXLINE];
  while(1){
	
     if((n=read(pipe_fd[0],line,MAXLINE))>0){
	printf("\nhi in serverpid %s",line);	
        line[n] = '\0';	
	if((sockfd=atoi(line))<=0){
	  serr("serverpid: wrong socket");
	}
	printf("\nserverpid socket :%d",sockfd);
	if((n=read(sockfd,filename,MAXLINE))==0){
                serr("serverpool: read socket failed");
	}
        filename[n] = '\0';
	printf("\nserverpid: file %s",filename);	
	if((fd=open(filename,O_RDONLY))<0)
	  serr("\nserverpid: open  file failed");

	while((n=read(fd,buf,MAXLINE))>0){
	   if(write(sockfd,buf,n)!=n){
	     serr("\ntcpserver: writing file.");
	   }
	}
     close(fd);
     }
   n=0;
  }
}
