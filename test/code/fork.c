#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t pid = fork();
	int stat = 0;
	switch(pid)
	{
		case -1:
			perror ("fork failed");
			exit(1);
			break;
		case 0:
			printf ("child\n");
			break;
		default:
			printf ("parent\n");
			break;
	}
	exit(0);
}

