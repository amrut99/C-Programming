/*
	This prints the error message and aborts the process with exit
error 1.
*/
#include "inet.h"
void serr(char *reason){

	fprintf(stderr,"%s\n",reason);
	exit(1);

}
