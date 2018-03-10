#include "apue.h"
#include <sys/select.h>

void sleep_us(unsigned int nusecs) {
    /* code */
    struct timeval tval;

    tval.tv_sec=nusecs/1000000;
    tval.tv_usec=nusecs%1000000;

    select(0,NULL,NULL,NULL,&tval);
}

int main(int argc, char const *argv[]) {

    printf("sleep 5 s\n");
    sleep_us(5*1000000);
    printf("sleep 5 s\n");
    sleep(5);
    return 0;
}
