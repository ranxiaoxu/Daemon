#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

void my_daemon()
{
	umask(0);
	pid_t id = fork();
	if(id > 0){   //father
		exit(0);
	}
	
	setsid();
	chdir("/");
	close(0);
	close(1);
	close(2);
   
	struct sigaction act;
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction(SIGCHLD, &act, NULL);
}
int main()
{
	printf("proc daemon begin...\n");
	my_daemon();
	while(1);
	return 0;
}
