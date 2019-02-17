/* Check checkargs.c : To check arguments*/
#include<dirent.h>
#include<sys/types.h>
#include<stdio.h>
void checkargs(int argc, char *argv[]){
  
  DIR *dirreturn;

  if(argc<3){
	fprintf(stderr,"\nERROR! Not enough arguments.\n"); 
	exit(0);
  }

 if((dirreturn=opendir(argv[1]))==NULL){
	fprintf(stderr,"\nERROR! Can not open source directory.\n"); 
	exit(0); 
  }
	
}
