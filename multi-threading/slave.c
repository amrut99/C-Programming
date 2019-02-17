/*
	This function is called by the thread_creat function in the main
process so this function runs as a thread. The funcion has the accept call as
the first function in the infinite loop. The accept will wait for the request
at that port and handle the request since all the threads has this accept call
all the threads are waiting for the request from the client. The thread
allocation for the request from the client is done by the operating system and
not by us.
	The slave accepts the username and password from the client and
authenticates it and checks the submission date late or on-time. The late
submission is accepted only once while the on time submission is accepted any
number of times. The slave returns a positive response to the client on success
or negative response on the failure.
	If the user is authenticated and the submission date check is done
successfully the server slave accepts the file data and stores the file with
appropriate name as 'late' or 'early'.
	After serving the client the thread again waits for the request from
the client.

*/

#include "inet.h"

void *slave(void *arg){
	int n,i,j,x,fd,newsockfd,*sockfd1,oldsockfd,sockfd;
	struct stat bstat;
	struct sockaddr_in cli_addr;
	socklen_t clilen;
	char buff[MAXLINE],login[LOGINLEN],password[LOGINLEN];
	char getbuff[MAXLINE];
	char response[MAXLINE]="1";
	char filename[MAXLINE],*passfile;
	
	sockfd1 = arg;
	oldsockfd = *sockfd1;
	printf("\n thread id 1: %d",pthread_self());

  while(1){
	sockfd = accept(oldsockfd,(SA *)&cli_addr, &clilen);
	printf("\n thread id 2: %d",pthread_self());
	if((n=read(sockfd,buff,MAXLINE))<0)serr("slave:read 1 failed.");
	i=0;j=0;
	while(buff[i]!=':'){
		login[j]=buff[i];	
		j++;i++;
	}
	login[j]='\0';j=0;i++;
	while(buff[i]!=':'){
		password[j]=buff[i];
		j++;i++;
	}
	password[j]='\0';j=0;i++;

	printf("\n%s,%s", login,password);
	if(authenticate(login,password)==0){
	  response[0]='0';response[1]='\0';
	  if(write(sockfd,response,n)!=n)serr("slave: write 2 failed.");
		printf("\nAuthentification failed.");
	  return;
	
	}
	printf("\nAuthentification Success!!!!");
	x=getstatus(month,day,year);
	if(x==0){
		printf("\nAssignment is late.");
		strcpy(filename,"late");
		if(stat(filename,&bstat)==0){
		  printf("\n No resubmition for late submission.");
		  response[0]='2';response[1]='\0';
		  n=strlen(response);
		  if(write(sockfd,response,n)!=n)serr("slave: write 3 failed.");
		  return;	
		}
	}
	if(x==1){
		printf("\nAssignment is on time.");
		strcpy(filename,"early");
	}
	n=strlen(response);
	if(write(sockfd,response,n)!=n)serr("slave: write 1 failed.");
	if((fd=open(filename,O_CREAT|O_RDWR|O_TRUNC,0700))<0)serr("file open");
	n=0;
	while((n=read(sockfd,getbuff,MAXLINE))>0){
	    if(write(fd,getbuff,n)!=n){
		close(fd);
		serr("slave: write 3 failed");
	    }
	}
	close(fd);
	  
	printf("\nDate: %d/%d/%d",month,day,year);
  }
/*if(close(sockfd)<0)serr("slave: close failed.");*/
exit(1);
}
