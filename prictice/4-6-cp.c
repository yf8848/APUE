#include "apue.h"
#include <stdio.h>
#include <fcntl.h>

const char* fin_name="./source.bin";
const char* fout_name="./out.bin";

char buf1[] = "#!/bin/bash";
char buf2[] = "date";

void create_file_contain_zero()
{

    int fd = open(fin_name,O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IXUSR);
    if(-1 == fd)
    {
        err_sys("open file error, when create file contain gap.");
    }

    int len_b1=sizeof(buf1)/sizeof(buf1[0]);
    int len_b2=sizeof(buf2)/sizeof(buf2[0]);

    if(len_b1 != write(fd, buf1,len_b1)){
        err_sys("write buf1 error");
    }

    // offset now 200
    if(-1 == lseek(fd,200,SEEK_CUR)){
        err_sys("lseek error");
    }

    if(len_b2 != write(fd,buf2,len_b2)){
        err_sys("write buf2 error.");
    }
    //exit(0);
}

int my_cp()
{
    printf("start my_cp\n");
    int fd=0,target=0;
    if((fd = open(fin_name,O_RDONLY)) == -1){
        err_sys("open the copy file error");
        return -1;
    }

    if((target = open(fout_name,O_RDWR|O_CREAT|O_TRUNC,S_IWUSR|S_IRUSR|S_IXUSR)) < 0)
    {
        err_sys("creat target file error");
        return -1;
    }

    char tmp;
    while(1 == read(fd,&tmp,1))
    {
        if(tmp != 0 ){
            write(target,&tmp,1);
            printf("%c", tmp);
        }
    }

    close(target);
    close(fd);
    return 0;
}

int main(int argc, char** argv){
    create_file_contain_zero();
    if(-1 == my_cp()){
	    err_sys("some errors occurs in my_cp");
    }

    return 0;
}
