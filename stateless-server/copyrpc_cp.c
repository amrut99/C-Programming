#include "inet.h"
#include "stateless.h"
int main(int argc, char *argv[]){
	CLIENT *cl;
	int fd1,n;
	struct stat s;
	char readline[MAXLINE];
	char *src, *dest,*server;
	data_t *data_return;
	readargs *readit;
	writeargs *writeit;
	nbytes_t *bytesn;

	if(argc<5){
	  printf("copyrpc <server> <operation> <local-file> <remote-file>\n");	
	  exit(1);
	}
	if(stat(argv[3],&s)<0){
	  printf("local file does not exist.\n");
	  exit(2);
	}
	server=argv[1];

	if((cl=clnt_create(server, STATELESS_FS_PROG,STATELESS_FS_VERSION,"tcp"))==NULL){
	  clnt_pcreateerror(server);
	  exit(2);
	}
	printf("\nRequesting client.");
	switch(atoi(argv[2])){
	case 1: if((fd1=open(argv[4],O_WRONLY|O_CREAT|O_TRUNC,0700))<0){
		  printf("copyrpc: open failed 1.");
		  exit(3);
		}
		printf("\nRead from server.\n");
		readit=(readargs *)malloc(sizeof(readargs));
		readit->filename=argv[3];
		readit->position=0;
		readit->nbytes=MAXLINE;
		data_return=(data_t *)malloc(sizeof(data_t));
		do{
			if((data_return=read_1(readit,cl))==NULL){
			  clnt_perror(cl,server);
			  exit(2);
			}
			printf("\n%s",data_return->buffer);
		if(data_return->n!=write(fd1,data_return->buffer,data_return->n)){
			printf("\ncopyrpc: write failed 1.");
			unlink(argv[4]); 
		}
			readit->position+=data_return->n;
		}while(data_return->n>0);
		break; 
	case 2:	if((fd1=open(argv[3],O_RDONLY))<0){
                  printf("copyrpc: open failed 1.");
                  exit(3);
                }
		printf("\nWriting to the server...\n");
		writeit=(writeargs *)malloc(sizeof(writeargs));
		writeit->filename=argv[4];
		writeit->position=0;
		while((writeit->nbytes=read(fd1,writeit->towrite.buffer,MAXLINE))>0){
			writeit->towrite.n=n;
			printf("\n%s",writeit->towrite.buffer);
		    if((bytesn=write_1(writeit,cl))==NULL){
			clnt_perror(cl,server);
                        exit(2);
		    }
		}
		
		break;
	default:
		printf("\nInvalid <operation> selection should be 1 or 2.\n");

	}

	clnt_destroy(cl);
	exit(0);

}
