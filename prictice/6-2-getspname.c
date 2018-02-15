#include "apue.h"
#include <shadow.h>

int
main(void)      // Linux,Solaris version 
{
    struct spwd *ptr;
    if((ptr=getspnam("foogao"))==NULL)
        err_sys("getspname error");
    printf("sp_pwdp = %s\n", ptr->sp_pwdp==NULL || ptr->sp_pwdp[0]==0?"null":ptr->sp_pwdp);
    exit(0);
}