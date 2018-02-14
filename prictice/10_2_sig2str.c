#include "apue.h"
#include <signal.h>

#define SIG2STR_MAX 1024
extern char* sys_siglist[];
int sig2str_my(int signo, char* str){
  char *tmp;
  if((tmp = sys_siglist[signo])!=NULL)
  {
    strncpy(str,tmp,SIG2STR_MAX);
    return 0;
    /* code */
  }
  return -1;
}

int str2sig_my(const char* str, int* signo)
{
  for
  return 0;
}


int main(int argc, char const *argv[]) {
  char msg[SIG2STR_MAX];
  int n=sig2str_my(SIGUSR1, msg);
  if((n != -1))
    printf("%d,%s\n",n,msg);
  return 0;
}
