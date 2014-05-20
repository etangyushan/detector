#include "./event.h"

#define MSGKEY (key_t)0x3ffff
struct mymsg
{
	long mytype;
	char even[1024];
};

int logevent (struct event ev)
{
	struct mymsg msg;
	int msgid, res;
	
	msgid = msgget(MSGKEY, 0666 | IPC_CREAT);
	printf ("msgid=%d\n", msgid);
	res = msgrcv (msgid, &msg, sizeof(msg), 0, 0);
	printf ("even1=%s\n", msg.even);

	return 0;
}


#if 1
int main()
{
	struct event ev;
	logevent (ev);
}
#endif
