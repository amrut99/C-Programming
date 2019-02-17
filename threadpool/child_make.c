#include "inet.h"

void child_make(int i, int listenfd, int addrlen){
	
	int pipefd[2];
	pid_t pid;
printf("\nmaking child......");
	if(pipe(pipefd)<0){
		serr("child_make: pipe failed.");
	}
	pid=fork();
	switch(pid){

	case 0:close(pipefd[1]);
                serverpid(pipefd,listenfd);
		break;
	case -1:
		printf("\nfork failed.\n");
		break;
	default:
	
	  cptr[i].child_pid = pid;
          cptr[i].child_pipefd=pipefd[1];
          cptr[i].child_status=0;
          close(pipefd[0]);
	}

	
return;	
}
