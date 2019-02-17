/*	Assignment #4
	course:cps565
	Amrut Borgaonkar
	Yan Wang
	Piraporn Lerstaveesin

	Problem: Implementation of a "remote file" storage server and its client processes
using BSD datagram sockets(with AF_INET address family, and connection-less protocol
TCP/IP) on different machines.
	The protocol for the file transfer can be stated as follows. The client will send a
remote file name to the server. The server will first check that whether the file exists on
the server. If it does then server will send -1 to the client to indicate the error else it
will send 0 to the client so that the client will start send file.If the file does exist on the 
server the client will terminate the execution.
	When the server receives the packet with the less number of bytes than the maximum
size of the buffer it indicates the end of file. 

	Solution: To tranfer the file from client to server we may implement UDP/IP server
and UDP client. The server will be concurrent server so that server can process multiple
clients at the same time. To implent a concurrent server we have to creat multiple child
server processes using a fork call. Each process will listen to the specified client.
	Since we are implementing UDP protocol. Each child-server will try to use the same
port, we have to provide a private port ( different from th eone main-server is accepting
connections at) to the client after a successful connection to server.
	The server will creat listening socket(5000 to 6000). Then the server will listen to
this socket for the request from the client. When it receives the request from the client it
creats a new private port for the client and a new process is created which provides the rest
of the service to the client and terminates after the complication.
	The client accepts the server address, server port, remote file path and a local file
path. The cliet then sends the remote file path to the server adn waits for the reply from
the server. On positive reply it will start transfering the local file data.
	
	Server: The program accepts the port address from the
user from the command line. Preferably the port address is ranging from
5000-6000. First it creates the socket. The bind gives the socket
'sockfd' the  local  address  my_addr. my_addr  is  addrlen  bytes
long. Then it calls the server function.
	
	Functions used:

	socket():creates enpoint for communication and returns a
                 descriptor. Socket can handle transfer of data in both
                  ways that is server to client and vice versa.

        bind():bind gives the socket sockfd the  local  address
                say my_addr.my_addr  is  addrlen  bytes  long.
                this is called "assigning a name to socket." 

	memset(): It sets the structure value to zero. It is used here to initialize the
		  structure. 
*/
#include "inet.h"
int main(int argc, char *argv[]){

	int sockfd;
	struct sockaddr_in serv_addr, cli_addr;
	void serr(char *);
	void server(int, SA *,int, struct sockaddr_in *);
	short port;

	if(argc<2){
		fprintf(stderr,"Usage: %s <server-port>\n", argv[0]);
		exit(1);
	}

	if((port = atoi(argv[1]))<=0) serr("udpserver: bad port");

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0)
		serr("udpserver: can't open datagram socket");

	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

	if(bind(sockfd, (SA *)&serv_addr, sizeof(serv_addr))<0){
		serr("udpserver: bind");
	}
	
	server(sockfd,(SA *)&cli_addr, sizeof(cli_addr), &serv_addr);

exit(0);
}
