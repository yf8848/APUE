#include "apue.h"
#include <fcntl.h>

int main(int argc, char const *argv[]) {
    int i,n;
    int fd[2];

    if (pipe(fd)<0) {
        /* code */
        err_sys("pipe error");
    }

    set_fl(fd[1],O_NONBLOCK);

    // write 1 byte at a time until pipe is full.
    for (n  = 0; ; n++) {
        /* code */
        if ((i=write(fd[1],"a",1))!=1) {
            /* code */
            printf("write return %d\n", i);
            break;
        }
    }
    printf("pipe capacity = %d\n", n);
    return 0;
}
