#include "./event.h"

//#define MSGKEY (key_t)0x3fff
#if 1
#define MSGKEY (key_t)0x28a2
struct mymsg
{
	long mytype;
	char even[1024];
};
#endif

int
logevent (struct event ev)
{
	struct mymsg msg;
	int msgid, res;
	char *janstr;
	//event_jansson(ev, &janstr);
	//printf("janstr=%s\n", janstr);
	event_jansson (ev, &msg.even);
	printf ("msg.even=%s\n", msg.even);
#if 0
	msg.mytype = 1;
	msgid = msgget (MSGKEY, 0666 | IPC_CREAT);
	res = msgsnd (msgid, &msg, sizeof (msg), 0);
	printf ("发送的json格式字符串: %s\n", msg.even);
#endif
	return 0;
}

#if 0
int
logevent (struct event ev)
{
	struct mymsg msg;
	int msgid, res;
	sprintf (msg.even, "{\"jsonStr\":\"{\"incID\":\"%s\",\"srcip\":\"%s\",\"desip\":\"%s\",\"protocol\":\"%s\",\"policyID\":\"%s\",\"snapshot\":\"%s\",\"fileName\":\"%s\",\"fileType\":\"%s\",\"filePath\":\"%s\",\"domain\":\"%s\"}\",\"commandKey\":\"11100112\"}", "1",
		 ev.nameinfo.srcip, ev.nameinfo.desip, "tcp", "0111", ev.nameinfo.snapshot, ev.nameinfo.filename, ev.nameinfo.fileformat, BETRANSFORM, "www.domain.com");

	/* strcpy(msg.even, "msg.even"); */
	msg.mytype = 1;
	msgid = msgget (MSGKEY, 0666 | IPC_CREAT);
	res = msgsnd (msgid, &msg, sizeof (msg), 0);
	printf ("发送的json格式字符串: %s\n", msg.even);

	return 0;
}
#endif

#if 0
int
main ()
{
	struct event ev;
#if 1
	strcpy (ev.nameinfo.nfexmsg.srcip, "192.168.1.13");
	strcpy (ev.nameinfo.nfexmsg.desip, "192.168.1.12");
	strcpy (ev.protocol, "tcp");
	strcpy (ev.policynum, "1234");
	strcpy (ev.nameinfo.transformname, "aaa.match");
	strcpy (ev.nameinfo.nfexmsg.filename, "aaa.doc");
	strcpy (ev.nameinfo.fileformat, "doc");
	strcpy (ev.filepath, "/root/log");
	strcpy (ev.domain, "domain");
#endif
	logevent (ev);
}
#endif
