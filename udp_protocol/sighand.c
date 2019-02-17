/*
To display error when the alarm is raised.

*/
int sighand(int signo)
{
 printf("Signal called : %d\n", signo);
}
