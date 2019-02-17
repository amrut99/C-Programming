#include<stdio.h>
#include<unistd.h>
int main(int arg, char *argv[]){
	FILE *fd;
	char *ptr, *salt="ab";
	char login[25], password[100];

	if(arg<3){
	   printf("error argc\n");
	   exit(0);
	}
	
	if((ptr = (char *)crypt(argv[2],salt))==NULL) printf("crypt failed\n");

	if((fd=fopen("password","a"))==NULL)
		printf("open failed.");
		fprintf(fd,"%s %s\n",argv[1],ptr);

exit(0);
}
