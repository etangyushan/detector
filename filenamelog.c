#include "./filenamelog.h"

/* 遍历文件夹，将文件夹下的文件名写入到记录文件 */
int
filenamelog (char *dirname, char *filenameall, char *filenameun)
{
	DIR *dir;
	struct dirent *ent;
	FILE *pf1;
	FILE *pf2;
	FILE *pf3;
	int c;

	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int flag;
	char buf[256] = { };
	struct namemsg nameinfo;

	//printf ("dirname=%s\n", dirname);
	//printf ("filename1=%s\n", filenameall);
	//printf ("filename2=%s\n", filenameun);
	//记录没有转换的文件名
	//判断文件夹是否为空
	if (isdirempty (dirname) == 0) {
		perror ("dir is empty");
		return -1;
	}

	dir = opendir (dirname);
	if (dir == NULL) {
		perror ("opendir");
		return -1;
	}
	//遍历文件夹，将文件夹中的文件名记录两份,分别到filename1.log和filename2.log中
	while (1) {
		ent = readdir (dir);
		if (ent <= 0) {
			break;
		}
		if ((strcmp (".", ent->d_name) == 0) || (strcmp ("..", ent->d_name) == 0) || (ent->d_type == 4)) {
			//printf ("d_type1=%d\n", ent->d_type);
			//printf ("d_name1=%s\n", ent->d_name);
			continue;
		}
		if (ent->d_type == 8) {
			//printf ("d_type2=%d\n", ent->d_type);
			//printf ("d_name2=%s\n", ent->d_name);
			//判断是否已经存在记录文件中
			flag = 1;
			//printf ("line1=%s\n", line);
			//fseek(pf3, 0, SEEK_SET);
			pf3 = fopen (filenameun, "r");
			//while ((read = getline (&line, &len, pf3)) != -1) 
			while ((read = fread (&nameinfo, sizeof (nameinfo), 1, pf3))) {
				printf ("filenamelog.c\n");
				if (strcmp (ent->d_name, nameinfo.transformname) == 0) {
					flag = 0;
					break;
				}
			}
			fclose (pf3);
			pf3 = NULL;
			if (flag == 1) {
				//printf ("line3=%s\n", line);
				//printf ("d_name3=%s\n", ent->d_name);
				memset (&nameinfo, 0, sizeof (nameinfo));
				sprintf (nameinfo.transformname, "%s\n", ent->d_name);
				//记录全部文件名
				pf1 = fopen (filenameall, "a");
				pf2 = fopen (filenameun, "a");
				fwrite (&nameinfo, sizeof (nameinfo), 1, pf1);
				fwrite (&nameinfo, sizeof (nameinfo), 1, pf2);
				fclose (pf1);
				pf1 = NULL;
				fclose (pf2);
				pf2 = NULL;
			}
		}
	}
	closedir (dir);

	printf ("写入文件名称完毕,filenamelog.c\n");

	return 0;
}

#if 0
int
main ()
{
	char *dirname = "bb";
#if 0
	int res = isdirempty (dirname);
	if (res == 0) {
		printf ("是空\n");
	}
	else {
		printf ("不是空\n");
	}
#endif

	char *filename1 = "a.log";
	char *filename2 = "b.log";
	logfilename (dirname, filename1, filename2);
}
#endif
