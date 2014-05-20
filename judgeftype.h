#ifndef JUDGEFTYPE_H_
#define JUDGEFTYPE_H_

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "./event.h"
#include "./mydebug.h"

#if 0
/* nfex发送的信息 */
struct nfexinfo
{
	char srcip[32];
	char desip[32];
	char filename[256];
};

/* 文件名信息 */
struct namemsg
{
	char transformname[256];
	char fileformat[32];
	struct nfexinfo nfexmsg;
};
#endif

/* 1:.doc, 2:.pdf, 3:.ppt */
//int filetotxt(char *dirname);
//int filetotxt(struct namemsg **name);
int filetotxt(struct namemsg *name);

/* 根据后缀判断文件类型 1:.doc, 2:.pdf, 3:.ppt*/
int file_type(char *fname);

#endif
