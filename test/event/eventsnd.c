#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

//#define MSGKEY (key_t)0x1ffff

#define MSGKEY (key_t)0x1022
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
	
	printf ("msg.even=%s\n", msg.even);
	strcpy (msg.even, "msg");
	strcpy (msg.even, "\"event\":[{\"flag\":\"1\"},{\"srcip\":\"192.168.1.13\", \"desip\":\"192.168.1.12\", \"protocol\":\"tcp\", \"policynum\":\"0111\", \"snapshoot\":\"aaa.match\", \"filename\":\"aaa.doc\", \"fileformat\":\"doc\", \"filepath\":\"/root/detector/before_transform\", \"domain\":\"www.domain.com\"}]");
	msgid = msgget(KEY, 0666 | IPC_CREAT);
	res = msgsnd (msgid, &msg, sizeof(msg), 0);
	//msg.mytype = 0;
	//res = msgrcv (msgid, &msg, sizeof(struct mymsg), 0, 0);
	printf ("even3=%s\n", msg.even);

	return 0;
}


#if 1
int main()
{
	logevent ();
}
#endif
