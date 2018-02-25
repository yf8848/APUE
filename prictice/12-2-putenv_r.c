#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

extern char** environ;
pthread_mutex_t mutex;

static pthread_once_t init_done = PTHREAD_ONCE_INIT;


static void thread_init(void)
{
	pthread_mutexattr_t attr;
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&mutex, &attr);
	pthread_mutexattr_destroy(&attr);
}

int putenv_r(char* str)
{
	int i,len;
	char *ptr_key=NULL;
	ptr_key=strchr(str,'=');
	if(NULL==ptr_key)
	{
		printf("Param illegal Usage: name=value\n");
		exit(0);
	}
	len = ptr_key-str;

	pthread_once(&init_done, thread_init);

	// 
	pthread_mutex_lock(&mutex);

	for(int i=0; NULL!= environ[i];i++)
	{
		if(0==strncmp(str,environ[i],len))
		{
			environ[i]=str;
			pthread_mutex_unlock(&mutex);
			return 0;
		}	
	}
	environ[i]=str;
	pthread_mutex_unlock(&mutex);
	return 0;
}

void show_env()
{
	for(int i=0; NULL!= environ[i];i++)
	{
		printf("%s\n",environ[i]);
	}
}

void* th_fun(void* arg)
{
	char* str=(char*)arg;
	putenv_r(str);
	show_env();
	return 0;
}
	

int main()
{
	char buf[1024]={"name=whoareyou"};
	
	pthread_t th;
	int err = pthread_create(&th,NULL, th_fun, buf);
	if(err!=0)
	{
		printf("create thread error\n");
	}

	pthread_join(th,NULL);
	
	show_env();
	
	return 0;
}
	
