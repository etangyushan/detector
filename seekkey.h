#ifndef SEEKKEY_H_
#define SEEKKEY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "./my_syslog.h"
#include "./tool.h"
#include "./mydir.h"
#include "./filenamelog.h"
#include "./judgeftype.h"
#include "./event.h"
#include "./acsmx.h"
#include "./policyjans.h"

/* 关键字结构体 */
struct policykey
{
	char keyword[256];
};

/* 判断是否匹配 ,匹配的关键字标志位为 "match"*/
struct policymsg  acsm_match_policy(ACSM_PATTERN *pattern, struct policymsg pinfo);

/* 产生匹配信息 */
//ACSM_STRUCT* acsmMatching(char *filePath, char **argv, int count,int maxLegth); 
ACSM_STRUCT* acsmMatching(char *filePath, char argv[][LENMAX], int count,int maxLegth);

/* 匹配关键字 */
struct policymsg seekkey(struct namemsg *nameinfo, struct policymsg policyinfo);
//int seekkey(struct namemsg *nameinfo, struct policymsg policyinfo);
//int seekkey(char *fname, char *keyword);

//int matchfile (char *dirname, char *keywordfile);
/* 对文件记录的.txt文件进行匹配 */
int matchfile (struct namemsg nameinfo, char *policyfile);

#endif
