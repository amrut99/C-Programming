/*This is a client program for remote date service.*/

#include<stdio.h>
#include<rpc/rpc.h>
#include "date.h"

main(int argc, char *argv[]){
	CLIENT *cl;
	char *server;
	long *lresult;
	char **sresult;
	
	if(argc<2){
		printf("\nusage:<executable><hostname>");
		exit(1);
	}
	server=argv[1];
	/*Create client handle.*/
	
	if((cl=clnt_create(server, DATE_PROG, DATE_VERS, "udp")) ==NULL){
		clnt_pcreateerror(server);
		exit(2);
	}
	
	/*call remote procedure "bin_date"*/
	
	if((lresult = bin_date_1(NULL,cl))==NULL){
		clnt_perror(cl, server);
		exit(3);
	}
	printf("time on host %s = %ld\n", server, *lresult);
	
	/*call remote procedure "str_date".*/
	
	if((sresult = str_date_1(lresult,cl))==NULL){
		clnt_perror(cl,server);
		exit(4);
	}
	printf("time on host %s = %s",server, *sresult);
	
	clnt_destroy(cl);
	exit(0);

}
