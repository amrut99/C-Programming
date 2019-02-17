/*
	Child Server: The child process sends the acknowledgement to the client which
contains '0'. It indicate the client to send the contents of the file it want to upload to
the server.
	The child server listens to the client using recvfrom function. It reads the data
fromt the read buffer and writes to the file which is created by the child-server. 
	According to the protocol when it reads the message having less bytes than the
maximum size of the buffer it stops accepting the data from the client because it indicates
end of file.
	On completion it exits from the process.  
	Functions used:
		open(): used to creat a file on the server.

		write(): write the data to the file.
		
		close(): Close the file and socket.
*/
#include "inet.h"
void filecopy(int sockfd, char *filename, SA *pcli_addr,int maxclilen){
  socklen_t clilen;
  int n,fd;
  struct stat *st;
  char *ptr,mesg[MAXLINE], buf[MAXSZ],ack[ACKSIZE];
  short seq=1,count;
                        buf[0]='0';buf[1]='\0';
                        ptr = mesg;
			copybyte(ptr,(char *)&seq,sizeof(seq));
			ptr = ptr + 2;			
                        count = strlen(buf); n = count; count = htons(count);
                        copybyte(ptr, (char *)&count, sizeof(count));
                        ptr = ptr + 2;
                        copybyte(ptr, buf, n + 1); n = n + 2 + 2 + 1;
	if((fd=open(filename,O_CREAT|O_WRONLY|O_TRUNC,0700))<0)
		serr("server: creating new file"); 

                  if(sendto(sockfd, mesg, n, 0, pcli_addr, clilen) != n)
                  serr("filecopy: sendto error1");

  clilen=maxclilen;
  while(1){
	
/*	printf("\nbefore recvfrom.");*/

	n = recvfrom(sockfd, mesg, MAXLINE, 0,pcli_addr, &clilen);
	if(n<0)serr("\nfilecopy : recvfrom failed.");
	ptr = mesg; seq = *(short *)ptr; seq = ntohs(seq);
  /*      printf("filecopy: seq seen: %d\n", seq); */
        ptr = ptr + 2; count = *(short *)ptr; count = ntohs(count);
/*        printf("filecopy: count seen:%d\n",count); */
        ptr = ptr + 2;
      /*printf("filecopy: request seen: %s\n",ptr);*/
        copybyte(buf,ptr,count);   
	if(write(fd,buf,count)!=count)serr("server: writing file");
	/*printf("sending acknowledgment = %d\n",seq);*/
	sprintf(ack,"%d",seq);
	if(sendto(sockfd, ack, ACKSIZE, 0, pcli_addr, clilen) != ACKSIZE){
                  serr("filecopy: sendto error1");
	}
	if(count< MAXLINE-4){
	 printf("\n end of file!");
	 break;
	}

  }
printf("File Transfer complete in filecopy\n");
close(sockfd);
close(fd);	
exit(0);
}
