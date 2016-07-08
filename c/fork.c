#include <stdio.h>
#include <unistd.h>

#define ITER_CNT	10
#define SLEEP_DURATION	10

void foo1()
{
	return;
}

void foo2()
{
	return;
}
int main()
{
	int i = 0;
	int ret = 0;
	pid_t pid;

	printf("Calling fork\n");
	pid = fork();
	if (pid == 0)
	{
		sleep(5);
		if (ret < 0)
		{
			perror("Exec process creation");
			return ret;
		}
		while(i++ < ITER_CNT)
		{
			printf("[%d] I am the child. i = %p\n", getpid(), &i);
			foo1();
			sleep(SLEEP_DURATION);
		}
	}
	else if (pid > 0)
	{
		printf("[%d] I am the parent. i = %p\n", getpid(), &i);
	}
	else
	{
		perror("Could not create new process\n");
		return pid;
	}
	printf("Exiting\n");
	return 0;
}
