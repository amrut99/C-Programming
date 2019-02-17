/*
	Name: Amrut Borgaonkar       Class: cps565
	      Yan Wang
	      Piraporn Lerstaveesin
	Assignment #3
	Due: 02/21/2001

    Problem:
	To implement a "remote file" copy server and its client using BSD
stream sockets AF_INET address family, and virtual circuit protocol TCP/IP
on different machines. The AF_INET decides the addressing family used in
the application which means the internet addressing.
	The server is concurrent server which means that it can handle
more than one request at the same time.
	The protocol for the file tranfer can be stated as follows. The
server will fulfil the client request for reading a file. It will check if
the requested file exists on the server. If it does exist, it will send
the file size followed by file contents else send a -1 to the client. The
server will close the socket to indicate end-of-file/ end-of-transaction
to client.
	The client program will be called 'client'. It will send the
remote-file-path for reading to server and wait for server's response. If
it receives a -1 from server, it will terminate. If it gets the file size
a value greater than zero, it will open the local-file-path for writing
and accept the contents of file from server and write them out to the
local file. If file to write already exists truncate it, creat it
otherwise.
	In case of problems client and server must perform clean up
actions before termination.	
	
    Solution:
	There will be two seperate programs client and server implemented
using TCP/IP protocol and using stream sockets AF_INET.
	The server program will creat a listening socket (socket address
be 5000 to 6000). It will bind the socket. Bind will assign a name to
unnamed socket. Then the server will listen to a  network  for  service
requests,  accepts  requests  when  they arrive, and invokes servers in
response to those service requests. The server accepts the file name to
be transfered from the socket. Since we want the server to be
concurrent once the server gets a request it will creat a child process
and the child process will perform the task of transfering the file data
from the server to the client if the file exists. Once the task is
completed it will terminate.
	The client will accept the server(host) IP address, the server
port, the file to be copied from the server and the file name on which it
wants to copy, from the command line. It will display error message if the
data entered is not correct. If it is correct the client will creat a
socket and will connect to the server. Once the connection is established
it will transfer the file name of the file it wants to copy through the
socket and wait for the reply from the client. According to the protocol
if the server sends the file size to the client the client onsiders that
the data sent next is the actual file and it starts coping the data to the
local file. If the server sends -1 it means to the client that the
requested file does not exist so it terminates.

    Server:
	The following server program follows the steps to start to accept
the request from the client. The program accepts the port address from the
user from the command line. Preferably the port address is ranging from
5000-6000. First it creates the socket. The bind gives the socket
sockfd the  local  address  my_addr. my_addr  is  addrlen  bytes
long. Then the listen function calls listens the created port for the
request from the client. The server is in infinite loop to accept the
requests continuesly. The accept function extracts the  first  connection
request  on  the queue  of  pending  connections, creates a new socket
with the same  properties  of parent socket,  and  allocates  a  new  file
descriptor for the socket. Once the new connection is established the
server creats spawns a child process and runs the server function in the
process memory by passing the socket descriptor to the server
function. This function does the actual transfer of the file to the
client. The waits for the request till it is terminated by the Crtl-c
signal. 

	Functions used:
	bzero():places n 0 bytes in the string.
	
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

	accept():The accept
	         function extracts the  first  connection  request  on
		 the queue  of  pending  connections, creates a new socket
		 with the same  properties  of socket value passed to it,
		 and allocates a new
		 file descriptor  for the socket.  If no pending
		 connections are present on the queue, and the socket is
		 not marked as non-blocking,  accept  blocks the caller
		 until a connection is present.  
	
	close(): closes the open file descriptor in this case used to
                 close the socket.
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

int main(int argc, char *argv[]){
	int sockfd, newsockfd;
	pid_t  pid;
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

	while(1){
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (SA *)&cli_addr, &clilen);
		if(newsockfd < 0) serr("tcpserver: accept error.");
		pid=fork();
		if(pid<0) serr("tcpserver: fork failed.");
		
		if(pid==0){
			server(newsockfd);
		}

		if(close(newsockfd)<0) serr("tcpserver: socket close.");
	}
exit(0);
}
