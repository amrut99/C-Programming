/*
	Assignment #5			Due: 04/04/2001
	Course cps565
	Name:Amrut Borgaonkar
	     Yan Wang
	     Piraporn Lerstaveesin
	
Problem:
	Learn POSIX and Solaris threads, Implementation of a multithreaded
"handin" server and its client processes using BSD stream-sockets (with
AF_INET address family, and TCP/IP protocol) on different machines.
	The client and server will communicate via BSD sockets and use
TCP/IP. The server in this case is going to be a multithreaded standing
server. It will serve more than one client at the same time by stting a pool of
service threads using POSIX threads. 
	The client program will 'submit' binary/executable file to the
server. It will conduct a dialog with the server and the user. 
	The server will perform checks on the requested file and accept it as
the requirements given in the assignment handout.

Solution:
	The client will submit the binary file,username and password. The
server will encrypt the password and check it with the password stored in the
'password' file if correct the server will proceed else it will reply 'login
failed' to the client. Then the server will check whether the file submission
date is early or late. If the file is early it will store as the 'early' else
it will store as the 'late'. The late submission is allowed only once while the
early submission is allowed any number of times.

Server:
	The following function is for the TCP server. The server just sets up
the main socket and port. Then the server creates the MAX_THREADS as the slave
threads and those slave threads will serve the request coming from the client.
	The main process will wait for the the threads to terminate and will be
idle.

Functions used:
	socket():creates enpoint for communication and returns a
                 descriptor. Socket can handle transfer of data in both
                  ways that is server to client and vice versa.

        bind():bind gives the socket sockfd the  local  address
                say my_addr.my_addr  is  addrlen  bytes  long.
                this is called "assigning a name to socket."

        listen(): To  accept  incoming  connections
                and  a  queue limit for incoming connections are specified
                with listen, and then the connections  are  accepted  with
                accept.The  listen  call  applies only to sockets of
                type SOCK_STREAM or SOCK_SEQPACKET.

	pthread_create(): Starts a new thread to execute function.
	
	pthread_join():Wait for the specified thread to terminate, exit status
		       available in status.



*/
#include "inet.h"

int main(int argc, char *argv[]){
	short servport;
	int sockfd,newsockfd,i,err;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;	
	pthread_t tid[MAX_THREADS];
	void *slave(void *arg);

	if(argc < 5)serr("server <serv-port> <month> <day> <year>");

	if((month=atoi(argv[2]))>12)serr("serv: wrong month");
	if((day=atoi(argv[3]))>31)serr("serv: wrong day");
	if((year=atoi(argv[4]))<0)serr("serv: wrong year");

	if((servport= (short)atoi(argv[1]))<=0)serr("serv: bad port");

	bzero((char *)&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family  = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(servport);

	
	if((sockfd = socket(AF_INET, SOCK_STREAM,0))<0)
		serr("serv: socket failed.");

	if(bind(sockfd, (SA *)&serv_addr, sizeof(serv_addr))<0)
		serr("serv: bind failed");
	
	if(listen(sockfd,QLEN)<0)serr("serv: listen failed.");

	for( i = 0; i < MAX_THREADS; i++){
           if(pthread_create(&tid[i], NULL, slave,(void *)&sockfd)!=0)
		printf("errno : %d",errno);
	}
	for(i=0;i<MAX_THREADS; i++){
	   pthread_join(tid[i],NULL);
	}
		
exit(0);
}
