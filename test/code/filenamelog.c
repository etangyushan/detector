#include "filenamelog.h" 

/* 判断文件夹是否为空 */
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

/* 遍历文件夹，将文件夹下的文件名写入到记录文件 */
int filenamelog(char *dirname, char *filenameall, char *filenameun)
{
	DIR *dir;	
	struct dirent *ent;
	FILE *pf1;
	FILE *pf2; 
	FILE *pf3; 
	int c;
	
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
    int flag;
	char buf[256] = {};

	printf ("dirname=%s\n", dirname);
	printf ("filename1=%s\n", filenameall);
	printf ("filename2=%s\n", filenameun);
	//记录全部文件名
	pf1 = fopen (filenameall, "a");
	//记录没有转换的文件名
	pf2 = fopen (filenameun, "a");
	pf3 = fopen (filenameun, "r");
	//判断文件夹是否为空
	if (isdirempty(dirname) == 0)
	{
		perror ("dir is empty");
		return -1;
	}

	dir = opendir (dirname);		
	if (dir == NULL)
	{
		perror ("opendir");
		return -1;
	}

	//遍历文件夹，将文件夹中的文件名记录两份,分别到filename1.log和filename2.log中
	while (1)
	{
		ent = readdir (dir);
		if (ent <= 0)
		{
			break;
		}
		if ((strcmp(".", ent->d_name)==0) || (strcmp("..", ent->d_name)==0) || (ent->d_type == 4))
		{
			//printf ("d_type1=%d\n", ent->d_type);
			//printf ("d_name1=%s\n", ent->d_name);
			continue;
		}
		if (ent->d_type == 8)
		{
			//printf ("d_type2=%d\n", ent->d_type);
			//printf ("d_name2=%s\n", ent->d_name);
			//判断是否已经存在记录文件中
			flag = 1;
			//printf ("line1=%s\n", line);
			fseek(pf3, 0, SEEK_SET);
			while ((read = getline (&line, &len, pf3)) != -1) 
			{
				 c = strlen (line);
				// printf ("line2=%s\n", line);
				 line[c-1] = '\0';
				 if (strcmp (ent->d_name, line) == 0)
				 {
					flag = 0;
					break;			
				 }
			}
			if (flag == 1)
			{
				//printf ("line3=%s\n", line);
				//printf ("d_name3=%s\n", ent->d_name);
				sprintf (buf, "%s\n", ent->d_name);
				fwrite (buf, sizeof(char), strlen(buf), pf1);
				fwrite (buf, sizeof(char), strlen(buf), pf2);
			}
		}
	}

#if 1
			if (line)
			{
				//printf ("sizelien=%s\n", strlen(line));
				free(line);
			}
#endif 

	fclose (pf1);
	pf1 = NULL;
	fclose (pf2);
	pf2 = NULL;
	fclose (pf3);
	pf3 = NULL;

	return 0;
}

#if 0 
int main()
{
	char *dirname = "bb";
#if 0
	int res = isdirempty(dirname);
	if (res == 0)
	{
		printf ("是空\n");
	}
	else
	{
		printf ("不是空\n");
	}
#endif 

	char *filename1 = "a.log";
	char *filename2 = "b.log";
	logfilename(dirname, filename1, filename2);
}
#endif 
