/*copydsrc2dest.c this function copies the source directory to the
destion directory*/

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>
#define PERMS 0777

void copydsr2dest(char *src, char *dest){
  
  struct dirent *readreturn;
  struct stat buff;
  char *srcfile, *destfile;
  DIR *dirret;
  int length,x;
  static int count=0;
  
  readreturn=(struct dirent *)malloc(sizeof(struct dirent));
  dirret=opendir(src);
  while((readreturn=readdir(dirret))!=NULL){
		
if((strcmp(readreturn->d_name,".")!=0)&&(strcmp(readreturn->d_name,"..")!=0)){

	  length=strlen(readreturn->d_name);
	  srcfile=(char *)malloc(strlen(src)+strlen("/")+length+1);
	  strcpy(srcfile, src);
	  strcat(srcfile,"/");
	  strcat(srcfile,readreturn->d_name);
	  destfile=(char *)malloc(strlen(dest)+strlen("/")+length+1);
	  strcpy(destfile, dest);
	  strcat(destfile,"/");
	  strcat(destfile,readreturn->d_name);

	x=stat(srcfile, &buff);
	if((buff.st_mode & S_IFREG)==S_IFREG){
		count++;
	  	copyfsrc2dest(srcfile,destfile);
	}
	if((buff.st_mode & S_IFDIR)==S_IFDIR){
		if(mkdir(destfile, PERMS)<0){
                fprintf(stderr,"\nmkdir failed in copydsrc2dest.c\n");
                exit(0);
                }
		copydsr2dest(srcfile,destfile);
	}

	free((void *)srcfile);
	free((void *)destfile);
	srcfile=NULL;
	destfile=NULL;
     }	

   }
printstats(count);
return;
}
