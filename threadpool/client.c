/*
	This reads the data from the socket which is connected to the
server and copies the data in the local file.
	The function gets the socket address, remote file name and local
file name from the calling process. It writes the remote file name to the
socket to ask the file from the server and reads the response from the
server by reading the socket.
	In this case according to the protocol it reads the socket first
time to find the response from the server. If it reads the data as -1 then
it translates it as the requested file does not exists on the server and
the client stops the execution. If it reads the value greater than zero it
accepts it as a file size then creats a new local file if it does not
exist or truncates the data  if it already exists. Then next data coming 
from the socket is the actual file data. Then it starts accepting the file 
data and writes it to the local file. 

	Functions used:
	read(): Read the data from the socket or file to the buffer
	
	write(): Write the data from the buffer to the file or socket
	
 	close(): Close the file
	
 	open(): Open or creat file.	



*/

#include "inet.h"

void client(int sockfd, char *rpath, char *lpath){

	int n,fd;
	char sendline[MAXLINE];
	strcpy(sendline, rpath);
	n=strlen(sendline);
	
	if(write(sockfd, sendline,n)!=n) serr("client: socket write");
	n=0;
	if((n=read(sockfd,sendline,MAXLINE))>0){
	  sendline[n]='\0';
	    if(strcmp(sendline,"-1")==0){
	  	serr("client: File not found");
	    } 
	    else{
		  printf("\nFile size is:%s\n",sendline);	
		  if((fd=open(lpath,O_CREAT | O_TRUNC |O_WRONLY,0700))<0){
		  serr("client:creating file");
	  	  }
	    }
	}
	else{
		serr("client: socket read.");
	}
	n=0;
	while((n=read(sockfd,sendline,MAXLINE))>0){
	  if(write(fd,sendline,n)!=n){
		unlink(lpath);
		serr("client: file write.");
	  }
	  
	}
	close(fd);
}
