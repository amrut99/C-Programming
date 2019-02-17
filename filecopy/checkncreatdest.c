/* checkncreatdest.c : To check and creat the destination directory */
#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#define PERMS 0777

void checkncreatdest(char *argv[]){
  
  DIR *dirreturn;
  int x;
  char choice;
  struct stat *buff;
  buff=(struct stat *)malloc(sizeof(struct stat));
	  x=stat(argv[2], buff);
	if((buff->st_mode & S_IFREG)==S_IFREG){

                fprintf(stderr,"\nERROR!! The destination is a file.\n");
                exit(0);
        } 
 

  if((dirreturn=opendir(argv[2]))==NULL){

	fprintf(stderr,"\nDestination directory does not exist\nDo you want to creat new directory[y/n]?");
	fscanf(stdin, "%c",&choice);
	
	switch(choice){
	case 'y':if(mkdir(argv[2], PERMS)<0){
		fprintf(stderr,"\nmkdir failed\n");
		exit(0); 
		}
		 break;
	case 'n':exit(0);
	default: exit(0);
	}
  }
copydsr2dest(argv[1],argv[2]);
}
