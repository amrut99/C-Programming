#include "inet.h"

void gettime(char * buff){

	long lrslt;
	char *ptr, *ctime();
	
	lrslt = time((long *) 0);
	ptr = ctime(&lrslt);
	sprintf(buff,"%s: %s", "Time on server is", ptr);

}
