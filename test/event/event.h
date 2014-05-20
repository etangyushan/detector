#ifndef EVENT_H_
#define EVENT_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include "./mydir.h"

/* 目的IP */
#define DESIP "10.63.99.149";
/* 源IP */
#define SRCIP "127.0.0.1";
/* 哪个协议 */
#define PROTOCOL "tcp";
/* 存放产生到匹配信息的目录 */
#define MATCHDIR "/root/detector/match"
/* 域名 */
#define DOMAIN "www.baidu.com";

/* 事件信息文件 */
#define EVENTLOG "/root/detector/log/eventmsg.log"
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


struct event 
{
	char protocol[16]; //协议
	char policynum[16];  //策略号
	char domain[32]; //域名
	char filepath[32]; //文件路径
	struct namemsg nameinfo;
};

int logevent(struct event ev);

#if 0
struct event2 
{
	char srcip[32];  //源ip
	char desip[32];  //目的ip
	char protocol[16]; //协议
	char policynum[16];  //策略号
	char snapshoot[32]; //快照
	char filename[256]; //文件名
	char fileformat[10]; //文件格式
	char filepath[256];  //文件路径
	char domain[32]; //域名
};
#endif


#endif
