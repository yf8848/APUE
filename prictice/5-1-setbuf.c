#include "apue.h"

/*
    apue prictise 5-1
    用setvbuf实现setbuf;
*/

void setbuf_test(FILE* restrict fp, char* restrict buf)
{
    if(fp==stderr || buf == NULL)
    {
        if(0!=setvbuf(fp,buf,_IONBF,BUFSIZ))
        {
            perror("setvbuf error.");
            exit(-1);
        }
        printf("no buf\n");
    }else{
        if(fp == stdin ||fp=stdout)
        {
            if(0!=setvbuf(fp,buf,_IOLBF,BUFSIZ)){
                perror("setvbuf error");
                exit(-1);
            }
            printf("line buff\n");
        }else{
            if(0!=setvbuf(fp,buf,_IOFBF,BUFSIZ)){
                perror("setvbuf error");
                exit(-1);
            }
            printf("Fill buff\n");
        }
    }
}


