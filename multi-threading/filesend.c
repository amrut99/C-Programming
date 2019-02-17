/*
	This function reads the data from the file and writes to the socket
descriptor to send the file data. Terminates when file reading is done.

*/
#include "inet.h"
void filesend(int sockfd, char *filename){
  int fd,n;
  char buff[MAXLINE];
	if((fd=open(filename,O_RDONLY))<0)serr("filesend: open failed.");
	printf("\nUploading file...");
	while((n=read(fd,buff,MAXLINE))>0){
	  if(write(sockfd,buff,n)!=n){
		close(sockfd);
		serr("filesend: write failed.");
	  }
	}
printf("\nFile upload complete.");

if(close(fd)<0)serr("filesend: file close failed");

}
