#ifndef  FILENAMELOG_H_
#define  FILENAMELOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "./judgeftype.h"

/* 遍历文件夹，将文件夹下的文件名写入到记录文件 */
int filenamelog(char *dirname, char *filenameall, char *filenameun);

#endif
