/*
	This function acts as a TCP client for the handin server. The client
sends the username and password to the server and waits for the reply from the
server. 
	If the user is authenticated successfully then the clients get positive
response else login failure response. If the client tries to resubmit the
assignment late then it will get the error response from the user.
	If the response from the user is positive then the client will send the
file to the server and stop when done.

*/
#include "inet.h"
int main(int argc, char *argv[]){

  struct sockaddr_in serv_addr, cli_addr;
  struct stat buff;
  ulong_t addr;
  struct hostent *hp;
  short servport;
  int statx,n,sockfd,newsock;
  char sendline[MAXLINE],response[MAXLINE];
  char login[LOGINLEN], password[LOGINLEN];
  char *ptr;

  if(argc < 4){
	serr("client: arguments failed");	
  }
  if(statx = stat(argv[3], &buff)<0){
	serr("client: file failed");
  }
  if((servport = (short)atoi(argv[2]))<=0)serr("client : bad port");
  
	if ((int)(addr = inet_addr(argv[1])) == -1) {
          serr("client: wrong ip address.");
        }

        hp = gethostbyaddr((char *)&addr, sizeof (addr), AF_INET);


        if(hp==NULL)serr("client: may be wrong IP address");

  if(write(1,"Login:",7)!=7) serr("client: login write failed");
  if((n=read(0,login,MAXLINE))<0)serr("client: login read failed");
	login[n-1]='\0';

  if(write(1,"Password:",10)!=10) serr("client: password write failed");
  if((n=read(0,password,MAXLINE))<0)serr("client: password read failed");
	password[n-1]='\0';

  strcpy(sendline,login);
  strcat(sendline,":");
  strcat(sendline,password);
  strcat(sendline,":");
  strcat(sendline,argv[3]);
 
  printf("\nstring : %s", sendline);	
	
  bzero((char *)&serv_addr, 0 , sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(addr);
  serv_addr.sin_port =htons(servport);

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0)serr("client : socket failed.");

  if(connect(sockfd, (SA *)&serv_addr, sizeof(serv_addr))<0)
	serr("client: connect failed.");

  n=strlen(sendline);

  if(write(sockfd,sendline,n)!=n)serr("client: write 2 failed");
  if((n=read(sockfd,response,MAXLINE))<0){
	close(sockfd);
	serr("client: read failed");
  }
  if(strcmp(response,"0")==0){
	printf("\nlogin failed!");
	return;
  }
  if(strcmp(response,"1")==0){
	printf("\nlogin successful!");
  }
  if(strcmp(response,"2")==0){
	printf("\nCan not resubmit late assignment.");
	return;
  }

  printf("\nResponse : %s ", response);

  filesend(sockfd, argv[3]);

  if(close(sockfd)<0)serr("client:socket close failed.");
  printf("\n");
  exit(0);
}
