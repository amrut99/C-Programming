#include "inet.h"

static int nchildren;

int main(int argc, char *argv[]){

	int sockfd,newsockfd,navail,i,n;
        pid_t  pid;
	char strsock[MAXLINE];
        socklen_t clilen;
        struct sockaddr_in cli_addr, serv_addr;
        short port;

        void serr(char *);
        void server(int);


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

	navail=nchildren;
	
	for(i=0;i<MAXCHILD;i++){
	  child_make(i,sockfd,sizeof(serv_addr));
	
	}

while(1){

          clilen = sizeof(cli_addr);
          newsockfd = accept(sockfd, (SA *)&cli_addr, &clilen);
          if(newsockfd < 0){
                 serr("tcpserver: accept error.");
          }
	  for(i=0;i<MAXCHILD;i++){
		if(cptr[i].child_status==0){

	           inttostr(newsockfd,strsock);
		   n=strlen(strsock);    
                   if(write(cptr[i].child_pipefd,strsock,n)!=n)
                   serr("serverpool : write pipe failed.");

		   cptr[i].child_status=1;	
   			
		   break;		
		}
	  }

          if(close(newsockfd)<0) serr("tcpserver: socket close.");
        }
			


exit(0);
}
