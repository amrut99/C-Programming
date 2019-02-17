#include "inet.h"

int main(int argc, char *argv[]){
	int sockfd, newsockfd,i,child_status,pipe_fd[2],n;
	char line[MAXLINE],socket_str[MAXLINE];

	pid_t  pid;
	socklen_t clilen;
	struct sockaddr_in cli_addr, serv_addr;
	short port;

	void serr(char *);
	void serverpid();

	if(argc<2){
		fprintf(stderr,"Usage: %s <srvr-port>\n",argv[0]);
		exit(1);
	}
	
	if((port = (short) atoi(argv[1]))<=0) 
	serr("tcpserver : bad port");
 	
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0)
	serr("tcpserver: socket error"); 
	 
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr= htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

	if( bind(sockfd, (SA *) &serv_addr, sizeof(serv_addr))<0)
		serr("tcpserver: bind error.");

	if(listen(sockfd, QLEN)<0)
		serr("tcpserver: listen error.");

	
	if(pipe(pipe_fd)<0){
		serr("serverpool: pipe failed");	
	}
	for(i=0;i<5;i++){
		
		pid=fork();
		if(pid<0) serr("tcpserver: fork failed.");
		
		if(pid==0){
			close(pipe_fd[1]);
			serverpid(pipe_fd);
		}		
		if(pid>0){
			close(pipe_fd[0]);
		}
	}

	while(1){

	  clilen = sizeof(cli_addr);
          newsockfd = accept(sockfd, (SA *)&cli_addr, &clilen);
          if(newsockfd < 0){
		 serr("tcpserver: accept error.");
	  }
	  if((n=read(newsockfd,line,MAXLINE))==0){
		serr("serverpool: read socket");
	  }
	   line[n]='\0';
		if(write(pipe_fd[1],line,n)!=n)
		  serr("serverpool : write pipe failed");
	 		
		
	  if(close(newsockfd)<0) serr("tcpserver: socket close.");
	}
}
