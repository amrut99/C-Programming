#include "inet.h"
void inttostr(int num, char numstr[521]){
	
	int digit,i,pos=0,n;
	char temp[521];
	char c;

	while(num>10){
	  digit=num%10;
	  c=digit+48;
	  temp[pos]=c;
	  num=num/10;
	  pos++;
	}
	temp[pos]=num+48;
	pos++;
	temp[pos]='\0';
	n=strlen(temp);
	pos=0;
	for(i=n-1;i>=0;i--){
	 numstr[pos]=temp[i];
	 pos++;
	}
	numstr[pos]='\0';

}
