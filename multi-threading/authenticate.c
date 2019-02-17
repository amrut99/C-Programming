/*
	This function authenticates the user by comparing the username and
password with the username and password stored in the 'password' file. 
	The passwords are stored in encrypted format in the 'password'
file. The password received is not in encrypted format so the password received
is first encrypted and then compared with the stored password.
*/
#include "inet.h"

int authenticate(char *login, char *password){
	char *passptr,*salt="ab";
	char tlogin[MAXLINE], tpassword[MAXLINE];
	FILE *fd;

	if((passptr = (char *)crypt(password,salt))==NULL)serr("crypt failed\n");
	if((fd=fopen("password","r"))==NULL)serr("authen: password file failed.");

  while( fscanf(fd,"%s %s",tlogin,tpassword)!=EOF){
	if((strcmp(tlogin,login)==0) && (strcmp(tpassword,passptr)==0)){
	if(fclose(fd)<0)serr("auth: file close failed.");
	 return(1);
	}
  }
if(fclose(fd)<0)serr("auth: file close failed.");
  return(0);
}
