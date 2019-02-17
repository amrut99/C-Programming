/*
	This function copies the source to destination byte by byte.
*/
#include "inet.h"
 
void copybyte(char *dst, char *src, int n){

	int i;
	for(i=0;i<n;i++){
		*dst++ = *src++;
	}
}
