#ifndef SSL_CLIENT_H_
#define SSL_CLIETN_H_

#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "./my_syslog.h"
#include "./computerstate.h"
#include "./mydebug.h"
#include "./judgeftype.h"

struct msgtransform
{
	long mytype;
	struct namemsg nameinfo;
};
struct msgmatch
{
	long mytype;
	char even[1024];
};

struct msgkey
{
	long mytype;
	char keybuf[256];
};



/* 发送线程 */
void *sendto_https_pthread (void *p);

/* 接收线程 */
void *recivefrom_https_pthread (void *p);

/* 发送到sftp服务器线程 */
void *sendto_sftp_pthread (void *p);

/* 匹配文件线程 */
void *match_file_pthread (void *p);

/* 转换文件线程 */
void *transform_file_pthread (void *p);

void *daemon_pthread (void *p);

void myqueue (int flag);

#endif
