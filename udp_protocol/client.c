/*
	The client sends the remote file path to the server using the socket and sendto
function and waits for the reply from the server using the recvfrom function. When it gets
reply from the server it reads the reply and if it contains -1 it aborts the program. If the
reply contains 0 it means the server is ready to accept data from the client so the client
starts reading the file content and sends the data to the server using sendto function.
	After every packet sent it waits for the acknowledgemnt. If after certain time
acknowledgemnt is not received it indiactes error.
	When the file is completed it stops the transmission and exits the program.
	
	Function used:
	recvfrom(): is used to receive data on a socket whether it
                    is in a connected state or not.
        sendto():is used to transfer the message to another transport end-point.
	
	Singnal handler which raises interrupt SIGALARM after a certain time. 			

*/
#include "inet.h"

extern void sighand(int);

void client(int sockfd, SA *pserv_addr, int servlen,char *dest, char *src){

  struct sigaction act;
	
	socklen_t dummylen;
	int n,fd,nb;
	char sendline[MAXLINE], ansbuf[MAXLINE-3],ackn[ACKSIZE];
	char *ptr, *prompt = "Service?";
	SA dummyadr;
	short seq, count,ack;
	void serr(char *);
	void copybyte(char *, char *, int);


  act.sa_handler = sighand;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;

  if (sigaction(SIGALRM, &act, NULL) < 0)
                serr("client : sigaction failed");


	seq = 1; count = strlen(dest); dest[count] = '\0';
	seq = htons(seq); n=count; count = htons(count);
	ptr = sendline; copybyte(ptr, (char *)&seq, sizeof(short));
	ptr = ptr + 2; copybyte(ptr, (char *)&count, sizeof(count));
	ptr = ptr + 2; copybyte(ptr, dest, n + 1); n = n + 2 + 2 + 1;
	
	if(sendto(sockfd, sendline, n, 0, pserv_addr, servlen) !=n)
		serr("client: sendto error");

	n = recvfrom(sockfd, sendline, MAXLINE, 0, pserv_addr, &servlen);
	if(n < 0) serr("client:recvfrom error");
	ptr = sendline; seq = *(short *)ptr; seq = ntohs(seq);
	printf("client: seq %d\n",seq);
	ptr = ptr + 2; count = *(short *)ptr; seq = ntohs(count);
	printf("client: count : %d\n", count);
	ptr = ptr + 2; printf("client: response : %s\n",ptr);
	
	if(0==strcmp(ptr,"-1")){
		printf("error! file exists on server");
		exit(1);
	}
	if((fd=open(src,O_RDONLY))<0){
                serr("client: error opening source file");
        }
        while((nb=read(fd,ansbuf,MAXLINE-4))>0){
         seq++;
	 ansbuf[nb]='\0';
         count = nb; n = count; count = htons(count);
/*	 printf("Bytes read=%d\n",nb); */
         ptr = sendline;copybyte(ptr,(char *)&seq,sizeof(short));
         ptr = ptr + 2; copybyte(ptr,(char *)&count, sizeof(count));
         ptr = ptr + 2; copybyte(ptr,(char *)&ansbuf,n + 1); n = n + 2 + 2 + 1 ;
        	if(sendto(sockfd,sendline,n,0,pserv_addr,servlen)!=n){
                   if(close(sockfd)<0)serr("client:error closing socket.");
                   if(close(fd)<0)serr("client: error closing file.");
        	}
/*	printf("\npacket sent= %d",seq); */
	 
alarm(5);

	  n = recvfrom(sockfd, ackn, MAXLINE, 0, pserv_addr, &servlen);
        if(n < 0) {
		/*serr("client:recvfrom error"); */
		printf("We need to resend packet\n");
	}
	else {
		alarm(0);
	}
/*	printf("received acknowledgement = %s",ackn); */
	ansbuf[0]='\0';
        }
printf("Done!!\n");
       if(close(fd)<0)serr("client: error closing file.");

         ansbuf[0]='\0';
         seq++;
         count = strlen(ansbuf); n= count; count = htons(count);
         ptr = sendline;copybyte(ptr,(char *)&seq,sizeof(short));
         ptr = ptr + 2; copybyte(ptr,(char *)&count, sizeof(count));
         ptr = ptr + 2; copybyte(ptr,ansbuf,n + 1); n = n + 2 + 2 + 1 ;
      
	if(sendto(sockfd,sendline,n,0,pserv_addr,servlen)!=n){
		serr("client: error send to 2");
	}
 

}
