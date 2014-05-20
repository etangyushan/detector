#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
//int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
//ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);

#define VALUE (key_t)0xffff

struct mymsg
{
	long mtype;
	char buf[256];
};

/* 创建消息队列 */
void myqueue (int flag)
{
	//int msgid = msgget (VALUE, 0);
	int msgid = msgget (VALUE, 0666|IPC_CREAT);
	if (msgid == -1)
	{
		perror("msgget");
		exit(-1);
	}

	struct mymsg msg = {1, "我发送数据了"};
	char buf[256] = {};
	sprintf (buf, "%d,%s\n", flag, msg.buf);
	strcpy (msg.buf, buf);
	int res = msgrcv (msgid, &msg, sizeof(msg), 0, 0);
	if (res == -1)
	{
		perror ("msgsend");
		exit (-1);
	}
	printf("msg.mtype=%d\n", msg.mtype);
	printf("msg.buf=%s\n", msg.buf);
}

int main()
{
	myqueue(1);	
}
