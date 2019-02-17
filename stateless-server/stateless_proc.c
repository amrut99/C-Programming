#include <stdio.h>
#include <rpc/rpc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "stateless.h"

data_t *read_1(readargs *readf){
	int fd;
	data_t *dataf;
	dataf =(data_t *)malloc(sizeof(data_t));
	if((fd=open(readf->filename,O_RDONLY))<0){
	 printf("stateless_proc:open failed 1.\n");
	 exit(1);	
	}
	lseek(fd,readf->position,SEEK_SET);
	if((dataf->n=read(fd,dataf->buffer,BUFFER_SIZE))>0){
	 close(fd);
	 return(dataf);	
	}	
	else{
	 dataf->n=0;
	 bzero(dataf->buffer,sizeof(dataf->buffer));
	 close(fd);
	 return(dataf);
	}

}

nbytes_t *write_1(writeargs *writef){
	int fd;
	static nbytes_t n;
	struct stat s;
	if(stat(writef->filename,&s)<0){
	  if((fd=open(writef->filename,O_WRONLY|O_CREAT|O_TRUNC,0700))<0){
	    printf("stateless_proc:open failed 2.\n");
	    exit(2);
	  }
	}
	else{
	  if((fd=open(writef->filename,O_WRONLY))<0){
            printf("stateless_proc:open failed 2.\n");
            exit(2);
          }
	}
	n=writef->nbytes;
	lseek(fd,writef->position,SEEK_SET);
	if(n!=write(fd,writef->towrite.buffer,n)){
	  printf("stateless_proc:error in write!\n");
	  exit(3);
	}
	close(fd);
	return(&n);
}
