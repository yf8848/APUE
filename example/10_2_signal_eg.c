#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void sig_user(int);	/* one handler for both signals */

int main()
{
	if( signal(SIGUSR1, sig_user) == SIG_ERR){
			printf("can't catch user1\n");
	}
	if( signal(SIGUSR2, sig_user) == SIG_ERR){
			printf("can't catch user2\n");
	}

	while(1){
			pause();
	}

	exit(0);
}

static void sig_user(int sig_no)
{
	if( sig_no == SIGUSR1 ){
			printf("received SIGUSER1\n");
	}else if( sig_no == SIGUSR2 ){
			printf("received SIGUSER2\n");
	}else{
			printf("received sig_no : %d\n",sig_no);
	}
}
