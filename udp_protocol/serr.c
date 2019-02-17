#include "inet.h"
void serr(char *reason){

	fprintf(stderr,"%s\n", reason);
	exit(1);

}
