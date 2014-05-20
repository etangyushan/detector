#ifndef TOOL_H_
#define TOOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

/* 判断文件夹是否为空 */
int isdirempty(char *dirname);

/* 从文件全名中去掉后缀提取名字 */
int split_name(char *str, char **out);

/* 从文件全名中把文件的后缀提取出来 */
//char *split_suffix(char *str);
int split_suffix(char *str, char **suffix);

/* 从字符串中分离出数字 */
int numcapture(char *str, int *cpunum, int size);

/* 获得文件大小 */
unsigned long get_file_size (const char *path);

//////////////////////////////////////////////////////////////////////////////////
/*这个函数实现了把一个文件的绝对路径和后缀去除，只留下文件名的功能
 * */
//找到最后的slash(/)
int last_mark (char *str, char mark);
//找到第一个dot(.)
int first_mark (char *str, char mark, int num);
int substr (char *srcstr, char **decstr, int lastslash, int firstdot);
int getname(char *file, char **name);
////////////////////////////////////////////////////////////////////////////////////

#endif
