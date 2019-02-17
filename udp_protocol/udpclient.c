/*
	Client: It accepts the server address, port, remote file path and local file path
from the user. It creats the socket and binds the socket to the server address. Then it calls
the client function which actually transfers the message to the server.
	The function basically performs error checks which contains the valid ip address and
the valid port address.
	
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

	int sockfd;
	ulong_t addr;
	struct hostent *hp;
	struct sockaddr_in cli_addr, serv_addr;
	void serr(char *);
	void client(int, SA *, int,char *, char *);
	short sport;

	if(argc <5){
	fprintf(stderr,"Usage: %s <server-addr> <server-port>< remote file> <local file> \n", argv[0]);
		exit(1);
	}

	if((sport = atoi(argv[2])) <=0) serr("client: bad port");
	
	
        if ((int)(addr = inet_addr(argv[1])) == -1) {
          serr("client: wrong ip address.");
        }

        hp = gethostbyaddr((char *)&addr, sizeof (addr), AF_INET);


        if(hp==NULL)serr("client: may be wrong IP address");
	
	memset((char *)&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(sport);

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) <0){
		serr("udpclient: cant open datagram socket");
	}

	bzero((char *)&cli_addr, sizeof(cli_addr));
	cli_addr.sin_family = AF_INET;
	cli_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	cli_addr.sin_port = htons(0);

	if(bind(sockfd, (SA *) &cli_addr, sizeof(cli_addr)) <0){
		serr("udpclient: cant bind local address");
	} 
	client(sockfd, (SA *)&serv_addr, sizeof(serv_addr),argv[3],argv[4]);

	if(close(sockfd)<0)
		serr("udpclient: socket close error");

	exit(0);
}
