#include "inet.h"

void gettime(char *buff){

	long lrslt;
	char *ptr;
	
	lrslt = (long) time((long *) 0);
	ptr = (char *)ctime(&lrslt);
	sprintf(buff,"%s :%s ", "Time on server is ",ptr);

}
