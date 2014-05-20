#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

int isdirempty(char *dirname)
{
	/* 打开要进行匹配的文件目录 */
	DIR *dir = opendir(dirname);
	struct dirent *ent;
	if (dir == NULL) 
	{
		perror("seekkey.c-98-opendir");
		return -1;
	}
	while (1)
	{
		ent = readdir (dir);
		if (ent <= 0)
		{
			break;
		}
		if ((strcmp(".", ent->d_name)==0) || (strcmp("..", ent->d_name)==0))
		{
			continue;
		}
		if ((ent->d_type == 4) || (ent->d_type == 8))
		{
			return -1;
		}
	}
	return 0;
}


int main()
{
	char *dirname = "aa";
	int res = isdirempty(dirname);
	if (res == 0)
	{
		printf ("是空\n");
	}
	else
	{
		printf ("不是空\n");
	}
}
