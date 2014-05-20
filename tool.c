#include "./tool.h"
/* 判断文件夹是否为空 */
int
isdirempty (char *dirname)
{
	/* 打开要进行匹配的文件目录 */
	DIR *dir = opendir (dirname);
	struct dirent *ent;
	if (dir == NULL) {
		perror ("filenamelog.c-29-opendir");
		return -1;
	}
	while (1) {
		ent = readdir (dir);
		if (ent <= 0) {
			break;
		}
		if ((strcmp (".", ent->d_name) == 0) || (strcmp ("..", ent->d_name) == 0)) {
			continue;
		}
		if ((ent->d_type == 4) || (ent->d_type == 8)) {
			return -1;
		}
	}
	closedir (dir);
	return 0;
}

/* 从字符串中分离出数字 */
int
numcapture (char *str, int *cpunum, int size)
{
	int *num = cpunum;
	int sum, flag, i;

	flag = 0;
	sum = 0;
	i = 0;

	while (1) {
		if (*str >= '0' && *str <= '9') {
			sum = sum * 10 + (*str - '0');
			str++;
			flag = 1;
		}
		else if (*str >= 'A' && *str <= 'z') {
			str++;
			flag = 2;
		}
		else {
			if (flag == 1) {
				*num = sum;
				sum = 0;
				num += 1;
				flag = 0;
				i++;
			}
			str++;
		}
		if (i >= size) {
			return 0;
		}
	}
}

/* 获得文件大小 */
unsigned long
get_file_size (const char *path)
{
	unsigned long filesize = -1;
	struct stat statbuff;
	if (stat (path, &statbuff) < 0) {
		return filesize;
	}
	else {
		filesize = statbuff.st_size;
		return filesize;
	}
}

//////////////////////////////////////////////////////////////////////////////////
/*@author etangyushan
 *这个函数实现了把一个文件的绝对路径和后缀去除，只留下文件名的功能
 * */
//找到最后的slash(/)
int
last_mark (char *str, char mark)
{
	int site = 0;
	int count = 0;
	while (site <= strlen (str)) {
		//printf("laststr=%c\n",str[site]);
		if (str[site++] == mark) {
			count = site;
		}
	}
	//printf("laststr=%c\n",str[count-1]);
	//printf("count=%d\n", count);
	return count - 1;
}

//找到第一个dot(.)
int
first_mark (char *str, char mark, int num)
{
	int count = num;
	int size = strlen (str);
	//printf("size=%d\n",size);
	//printf("str:%s\n", str);
	while (size--)
		//while(1)
	{
		//printf("char----%d\n",str[count]);
		//printf("char----%c\n",str[count]);
		if (str[count] == mark) {
			break;
		}
		count++;
	}
	//printf("char----%c\n",str[count]);
	return count;
}

int
substr (char *srcstr, char **decstr, int lastslash, int firstdot)
{
	int i = 0;
	//int ls = lastslash;
	char *str = *decstr;
	//printf("last=%d,first=%d\n", lastslash, firstdot);
	//printf("size=%d\n", firstdot-lastslash);
	//printf("srcstr=%s\n", srcstr);
	int size = firstdot - lastslash - 1;
	lastslash++;
	for (i = 0; i < size; i++) {
		//str[i] = srcstr[ls++];
		//      printf("...%c...\n",srcstr[lastslash]);

		str[i] = srcstr[lastslash];
		lastslash++;
	}
	return 0;
}

int
getname (char *file, char **name)
{
	int lastnum = last_mark (file, '/');
	//printf ("lastnum=%d\n", lastnum);
	int firstnum = first_mark (file, '.', lastnum);
	//printf ("firstnum=%d\n", firstnum);
	substr (file, name, lastnum, firstnum);
	//printf ("name = %s\n", name);
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////
//
/* 从文件全名中把文件的后缀提取出来 */
int
split_suffix (char *str, char **suffix)
{
	//printf ("split_suffix============92\n");
	char *new = *suffix;
	int lastnum = last_mark (str, '/');
	int firstnum = first_mark (str, '.', lastnum);
	str += firstnum;
	//printf("ok\n");
#if 0
	int i;
	for (i = 0; i < firstnum - 1; i++) {
		str++;
	}
#endif
	//printf("ok2-str=%s\n",str);
	while (*new++ = *str++) {
		//      printf("ok3\n");
	}
	//printf("new=%s,size=%d\n",new, sizeof(new));
	return 0;
}

/* 从文件全名中去掉后缀提取名字 */
int
split_name (char *str, char **out)
{
	char buf[100] = { };
	char *new = str;
	int i = 0;
	while (1) {
		if (*new == '.') {
			break;
		}
		buf[i] = *new++;
		i++;
	}
	printf ("new=%s\n", new);
	strcpy (*out, buf);
	//printf("buf=%s\n", buf);
	return 0;
}

#if 0
/* 从文件全名中把文件名提取出来,没有后缀 */
int
main ()
{
#if 0
	while (1) {
		char *str = "aaaa.doc";
		char *suf = (char *)malloc (32);
		printf ("suf:%s\n", suf);
		//split_suffix(str, &suf);
		split_name (str, &suf);
		printf ("suf:%s\n", suf);
	}
#endif
	//char *file = "/root/etc/init.d/mytettttt.c";
#if 0
	char *file = "/a/mytettttt.c";
	char *name = (char *)malloc (256);
	int lastnum = last_mark (file, '/');
	//printf ("lastnum=%d\n", lastnum);
	int firstnum = first_mark (file, '.', lastnum);
	//printf ("firstnum=%d\n", firstnum);
	substr (file, &name, lastnum, firstnum);
	printf ("name = %s\n", name);
	free (name);
	name = NULL;
#endif

	while (1) {
		char *file = "/a/mytettttt.c";
		char *name = (char *)malloc (256);
		int res = getname (file, &name);
		printf ("name = %s\n", name);
	}
	return 0;
}
#endif
