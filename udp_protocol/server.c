/*
	Server: The server is in infinite loop to accept the requests continiously. The
recvfrom function listens to the request from the client. When it gets the first request it
reads the packet and and reads the filename from the packet. If the file already exist on the
server then the server sends a reply packet having value '-1' which indicates error to the
client. When the client receives it, it will not send file data.
	If the file does not exist on the server then it will the server have to creat a
child server which will provide the service to the client. So the server creats a new socket
and new server address but the port address attached to the server address is other than the
main port address then it binds the socket with this server address and then a new client
address is generated and the client address is copied in it. The new client address and
socket is passed to the child server. 
	The child server then provides the service to the client and the parent server is
again free to accept request from the other clients.

	Functions used:
	recvfrom(): is used to receive data on a socket whether it
    		    is in a connected state or not. 
	sendto():is used to transfer the message to another transport end-point.

	fork(): Forks a new child process and calls the server function in
                it.
    
	Data structure:
        struct sockaddr_in {
        sa_family sin_family;
        in_port_t sin_port;
        struct in_addr sin_addr;
        char sin_zero[];
        }
        is used to fill up the information with protocol, host
        address and port information. The host address is the IP address
        of the server and the port address is of the port address of the
        sever.	
		
*/
#include "inet.h"

void server(int sockfd, SA *pcli_addr, int maxclilen, struct sockaddr_in *serv){
	struct sockaddr_in *temp_serv_addr;
	SA *temp_cli_addr;
	socklen_t clilen;
	int n,x,temp,newsockfd;
	pid_t pid;
	char mesg[MAXLINE], *ptr,filename[MAXLINE], buf[MAXSZ];
	short seq,count;
	struct stat *st;
	void serr(char *);
	void copybyte(char *, char *, int);
	void filecopy(int,char *,SA *, int);
	clilen = maxclilen;

	while(1){
		printf("Waiting for req..........\n");
		pcli_addr =(SA *)malloc(sizeof(SA));
		n = recvfrom(sockfd, mesg, MAXLINE, 0, pcli_addr, &clilen);
		printf("Req received!!\n");
		if(n<0) serr("server: recvfrom error1");

		ptr = mesg; seq = *(short *)ptr; seq = ntohs(seq);
		printf("server: seq seen: %d\n", seq);
		ptr = ptr + 2; count = *(short *)ptr; count = ntohs(count);
		printf("server: count seen:%d\n",count);
		ptr = ptr + 2; printf("server: request seen: %s\n",ptr);
		strcpy(filename,ptr);
		/*copybyte(filename,ptr,count); */
		printf("filename:   %s", filename);
		if((x=stat(filename,&st))<0){
			printf("\nfile does not exist");

		if((newsockfd = socket(AF_INET, SOCK_DGRAM, 0))<0)
                serr("udpserver: can't open datagram socket");
		temp_serv_addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
       
	 	memset((char *) temp_serv_addr, 0, sizeof(*temp_serv_addr));
		copybyte((char *)temp_serv_addr, (char *)serv, sizeof(*serv));
/*        	temp_serv_addr.sin_family = AF_INET;
        	temp_serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
*/        	temp_serv_addr->sin_port = htons(0);

	        if(bind(newsockfd, (SA *)temp_serv_addr, sizeof(*temp_serv_addr))<0){
        	        serr("udpserver: bind");
        	}
			
		 temp_cli_addr =(SA *)malloc(sizeof(SA));
		 printf("size of cli = %d",sizeof(pcli_addr));
		 copybyte((char *)temp_cli_addr, (char*)pcli_addr, sizeof(SA));
		 printf("size of temp= %d",sizeof(temp_cli_addr));

			pid=fork();
			if(pid==0){
			  filecopy(newsockfd,filename,temp_cli_addr, sizeof(SA));
			}
			if(pid<0){
			  printf("fork failed.\n");
			}
		}
		else{
			printf("\nfile exist");
			temp =-1;
			sprintf(buf,"%d",temp);
			ptr = mesg + 2;
        	                count = strlen(buf); n = count; count = htons(count);
                        copybyte(ptr, (char *)&count, sizeof(count));
                        ptr = ptr + 2;
                        copybyte(ptr, buf, n + 1); n = n + 2 + 2 + 1;
		  if(sendto(sockfd, mesg, n, 0, pcli_addr, clilen) != n)
		  serr("server: sendto error1");
		}

		n=0;
	
	}
	
}
