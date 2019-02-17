/*
	This function checks the file status that is whether the submission is
late or on time. It calculates the number of seconds since 00:00:00 UTC,
January 1, 1970. Then it calculates the time at the very moment in the same
way. So if the time of the submission is less than the current then it is on
time else it is late assignment. The required value is returned.

*/
#include "inet.h"

int getstatus(int month,int day,int year){
   struct tm new;
   long tnew, tnow;

   new.tm_sec = new.tm_min = new.tm_wday = new.tm_yday = 0;
   new.tm_isdst = 0;
   new.tm_hour = 11;
/*   new.tm_gmtoff = 0;
   new.tm_zone = NULL;*/
   new.tm_mon = month-1;
   printf("mon: %d\n", new.tm_mon);
   new.tm_mday = day-1;    
   printf("mday: %d\n", new.tm_mday);
   new.tm_year = year - 1900;
   printf("year: %d\n", new.tm_year);


   tnew = mktime(&new) + 86500;
   if (tnew < 0) serr("mktime..failed");
   tnow = time((time_t) 0);

   printf("tnow: %ld, tnew: %ld\n", tnow, tnew);
   if (tnow > tnew){
	 printf("\nIt is late..\n");
	 return(0);
   }
   else{
	 printf("\nIt is early..\n");	
	 return(1);
   }

}
