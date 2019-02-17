/*
	This is a client using the TCP/IP protocol. The client undergoes
the following steps in TCP/IP protocol. It creates the socket binds the
socket with the server this binding is not exactly needed and then
connects to the server using the socket. Once the client is conneced to
the server the client can read and write the data through the socket.
	While connecting to the server the client never specifies its IP
address and port address to complete 5-tuple which establishes a unique
connection. The client IP address and port address are decided as a side
effect of the connection call.
	This case once the connection is established with the server the
client calls the 'client' function which accepts the file data trasfered
by the server and copies the data to the local file.

	Functions used:
	atoi():  converts the string into integer.
	
	bzero():places n 0 bytes in the string.

	socket():creates enpoint for communication and returns a
		 descriptor.
	close(): closes the open file descriptor in this case used to
		 close the socket.
	inet_addr():function  converts  the  Internet   host
	            address from numbers-and-dots notation into binary
		    data in  network  byte  order. 
	
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
	int sockfd,l;
	ulong_t addr;
	char *cp;
	extern int h_errno;
	struct hostent *hp;
	struct sockaddr_in serv_addr;
	short srvrport;

	void serr(char *);
	void client(int,char*,char*);

	if(argc<5){
		fprintf(stderr,"not enough para");
		exit(1);
	}
    if((srvrport= (short) atoi(argv[2]))<=0) serr("tcpclien:bad port");
	l=strlen(argv[1]);

	if ((int)(addr = inet_addr(argv[1])) == -1) {
	  serr("client: wrong ip address.");
	}

	hp = gethostbyaddr((char *)&addr, sizeof (addr), AF_INET);
        
	
	if(hp==NULL)serr("client: may be wrong IP address");

	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htonl(srvrport);

	if((sockfd = socket(AF_INET, SOCK_STREAM,0))<=0)
		serr("tcpclient: socket open");

	if(connect(sockfd, (SA *) &serv_addr, sizeof(serv_addr))<0)
		serr("tcpclient:connect error");

	client(sockfd,argv[3],argv[4]);

	if(close(sockfd)<0) serr("tcpclient: socket close");
	exit(0);
	
}
