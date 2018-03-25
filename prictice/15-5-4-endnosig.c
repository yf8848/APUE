#include "apue.h"

static void	sig_pipe(int);		/* our signal handler */

int
main(void)
{
	int		n, fd1[2], fd2[2];
	pid_t	pid;
	char	line[MAXLINE];
	FILE *fpin,*fpout;	//声明文件句柄

	/*
	if (signal(SIGPIPE, sig_pipe) == SIG_ERR)
		err_sys("signal error");
	*/

	if (pipe(fd1) < 0 || pipe(fd2) < 0)
		err_sys("pipe error");

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid > 0) {							/* parent */
		close(fd1[0]);
		close(fd2[1]);

		//将标准IO流同管道描述符关联
		if(NULL==(fpin = fdopen(fd2[0],"r")))
			err_sys("fdopen error.");
		if(NULL==(fpout=fdopen(fd1[1],"w")))
			err_sys("fdopen error.");

		// 将标准io流设置为行缓冲
		if(setvbuf(fpin, NULL,_IOLBF,0)<0)
			err_sys("setvbuf error.");
		if(setvbuf(fpout,NULL,_IOLBF,0)<0)
			err_sys("setvbuf error.");

		while (fgets(line, MAXLINE, stdin) != NULL) {
			/*
			n = strlen(line);
			if (write(fd1[1], line, n) != n)
				err_sys("write error to pipe");
			if ((n = read(fd2[0], line, MAXLINE)) < 0)
				err_sys("read error from pipe");
			if (n == 0) {
				err_msg("child closed pipe");
				break;
			}
			*/
			//line[n] = 0;	/* null terminate */

			if (fputs(line,fpout)==EOF) {
				/* code */
				err_sys("fputs error to pipe.");
			}

			if (fgets(line, MAXLINE,fpin)==NULL) {
				/* code */
				err_msg("child closed pipe.");
				break;
			}

			if (fputs(line, stdout) == EOF)
				err_sys("fputs error");
		}

		if (ferror(stdin))
			err_sys("fgets error on stdin");
		exit(0);
	} else {									/* child */
		close(fd1[1]);
		close(fd2[0]);
		if (fd1[0] != STDIN_FILENO) {
			if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)
				err_sys("dup2 error to stdin");
			close(fd1[0]);
		}

		if (fd2[1] != STDOUT_FILENO) {
			if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
				err_sys("dup2 error to stdout");
			close(fd2[1]);
		}
		if (execl("./add2", "add2", (char *)0) < 0)
			err_sys("execl error");
	}
	exit(0);
}

static void
sig_pipe(int signo)
{
	printf("SIGPIPE caught\n");
	exit(1);
}

/** term 1
$ ./15-5-pipe_stdio
*/

/**
$ killall -9 add2
*/

/** term 1
1 3
SIGPIPE caught
$ echo $?
141
*/
