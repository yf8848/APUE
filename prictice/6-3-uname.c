#include "apue.h"
#include <sys/utsname.h>

int
main(void)
{
    struct utsname uts;
    if(-1 == uname(&uts))
    {
        err_sys("uname error.");
    }

    printf("%s %s %s %s %s %s\n",uts.sysname,uts.nodename,uts.release,uts.version,uts.machine,uts.__domainname);

    exit(0);
}