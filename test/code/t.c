#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MATCHVALUE (key_t)0x1fff
#define SEEKVALUE (key_t)0x2fff

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
	char initname[256];
	char transformname[256];
	char fileformat[32];
	struct nfexinfo nfexmsg;
};

#if 0
struct mymsg
{
	long mtype;
	struct namemsg nameinfo;
};
#endif

int main()
{
	int msgid, res;
	char msg[256] = {};
	strcpy(msg,"send");
//	struct nfexinfo msg;
//	msgid = msgget (MATCHVALUE, 0666|IPC_CREAT);
//	res = msgrcv (msgid, &msg, sizeof(msg), 0, 0);
	struct namemsg nameinfo;
	//memset(&nameinfo, 0, sizeof(struct namemsg));
	char *fullname = "aaa.log";
	//strcpy (msg.nameinfo.transformname, fullname);
	strcpy (nameinfo.transformname, fullname);
	/* 发送消息队列给匹配线程 */
	msgid = msgget (SEEKVALUE, 0666|IPC_CREAT);
	//res = msgsnd (msgid, &nameinfo, sizeof(struct namemsg), 0);
	res = msgrcv (msgid, &nameinfo, sizeof(struct namemsg), 0, 0);
	if (res == -1)
	{
		perror("ssl_client.c-49-msgrcv");
	}
}
