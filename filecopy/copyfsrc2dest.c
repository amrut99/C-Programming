/*copyfsrc2dest.c:  This function copies the source file to destination file*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#define BF 1024
#define PERM 0666
void copyfsrc2dest(char *srcfile, char *destfile){
int fdin,n,fdin2;
  char buf[BF];

	fprintf(stdout,"\ndest:%s",destfile);
        if((fdin=open(srcfile,O_RDONLY))<-1){
          fprintf(stderr,"\nERROR! Opening file\n"); exit(0);
        }

        if((fdin2=open(destfile,O_CREAT| O_WRONLY| O_TRUNC, PERM))<-1){
        fprintf(stderr,"\nerror! can not open file"); exit(0);
        }

        while((n=read(fdin,buf,BF))>0){
          if(write(fdin2,buf,n)!=n){
                fprintf(stderr,"\nerror! could not copy\n"); exit(0);
          }

        }
        close(fdin);
return;
}
