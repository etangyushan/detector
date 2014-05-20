#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
//#define MSGKEY (key_t)0x3ffff
#define MSGKEY (key_t)0x28a2
struct mymsg
{
	long mytype;
	char even[1024];
};
#if 0
int logevent (struct event ev)
{
	struct mymsg msg;
	int msgid, res;
	
	msgid = msgget(MSGKEY, 0666 | IPC_CREAT);
	printf ("msgid=%d\n", msgid);
	strcpy(msg.even, "11111111");
	//res = msgrcv (msgid, &msg, sizeof(msg), 0, 0);
	res = msgsnd (msgid, &msg, sizeof(msg), 0, 0);
	printf ("even1=%s\n", msg.even);

	return 0;
}
#endif

int logevent ()
{
	struct mymsg msg;

	int msgid, res;
	memset (msg.even, 0, 1024);	
	msgid = msgget(MSGKEY, 0666 | IPC_CREAT);
	printf ("msgid=%d\n", msgid);
	strcpy(msg.even, "11111111");
	//res = msgrcv (msgid, &msg, sizeof(msg), 0, 0);
	res = msgsnd (msgid, &msg, sizeof(msg), 0);
	printf ("even1=%s\n", msg.even);

	return 0;
}


#if 1
int main()
{
	logevent ();
}
#endif
