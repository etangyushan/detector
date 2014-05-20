#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

#define KEY (key_t)0x1022

///#define KEY (key_t)0x1ffff
struct mymsg
{
	long mytype;
	char even[1024];
};

int logevent ()
{
	//int flag = 1;
	//char even[1024] = {};
	int msgid, res;
	struct mymsg msg;
	//memset(&msg, 0, sizeof(msg));
	
	msgid = msgget(KEY, 0666 | IPC_CREAT);
	//res = msgsnd (msgid, &msg, sizeof(msg), 0);
	//printf ("even1=%s\n", msg.even);
	//sleep(2);
	//printf ("even2=%s\n", msg.even);
	//msg.mytype = 0;
	res = msgrcv (msgid, &msg, sizeof(struct mymsg), 0, 0);
	printf ("even3=%s\n", msg.even);

	return 0;
}


#if 1
int main()
{
	logevent ();
}
#endif
