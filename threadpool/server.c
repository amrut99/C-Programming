/*
	The server function accepts the socket descriptor from the calling
process and reads the socket. The server reads the name of the file to be
transfered which is sent by the client.
	Once the name of the file is read the server tries to open the
file if the open function returns the negative value it means the file
does not exist or it is unable to open, in this case the server sends -1
to the client by writing to the socket. 
	If the file exists then it find the file size using stat system
call. Then the server sends the file size to the client by writing the
file size to the socket. Then it immediately starts sending the data in
the file by reading the file till the end of the file.
	
	Functions used:
	stat(): Used to find the file size.
	open(): Opens the existing file. If file does not exist or
		corrupted then returns -1.
	read(): Read the data from the file into the buffer
	write(): Write the data into the file from the buffer, in this
		 case to write to the socket descriptor.
	close(): close the socke and the file descriptor.

*/
#include "inet.h"

void server(int sockfd){
	int n,fd,x;
	char line[MAXLINE],buf[MAXLINE];
	struct stat buff;

	if((n=read(sockfd,line,MAXLINE))==0){
		serr("server: socket read");
	}
	
	if(n<0) serr("server:socket read.");
	
	line[n] = '\0';
	
	if((fd=open(line,O_RDONLY))<0){
		strcpy(line,"-1");
		n=strlen(line);
		if(write(sockfd,line,n)!=n){
                    serr("tcpserver: writing -1.");
		    close(sockfd);
                }
		
	}
	else{
	 	if((x=stat(line, &buff))<0){
			serr("server: stat failed");
		}
		sprintf(line,"%d",buff.st_size);  

		n=strlen(line);
	
		if(write(sockfd,line,n)!=n){
                    serr("tcpserver: writing size of file.");
        	}
		n=0;
		while((n=read(fd,buf,MAXLINE))>0){
		  if(write(sockfd,buf,n)!=n){
		    if(close(sockfd)<0)serr("server: closing socket");
		    if(close(fd)<0)serr("server: closing file");
		    serr("tcpserver: writing file.");
		  }
		}
	  if(close(sockfd)<0)serr("server: closing socket");
	  if(close(fd)<0)serr("server: closing file");
	}
	
 exit(0);
}
