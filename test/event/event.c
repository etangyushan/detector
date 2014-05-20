#include "./event.h"

//#define KEY (key_t)0x1022
//#define KEY (key_t)0x1ffff
#define MSGKEY (key_t)0x1022
struct mymsg
{
	long mytype;
	char even[1024];
};

#if 0
//int logevent(char *filename, char *snapshoot)
int logevent(struct event ev)
{
	int flag = 1;
	char even[1024] = {};
	FILE *pf;
	pf = fopen (EVENTLOG, "a");
	//printf ("even.snapshoot=%s\n", ev.snapshoot);
	sprintf (even, "{\"%s\":\"%s\", \"%s\":\"%s\", \"%s\":\"%s\", \"%s\":\"%s\", \"%s\":\"%s\", \"%s\":\"%s\", \"%s\":\"%s\", \"%s\":\"%s\", \"%s\":\"%s\"}", 
					"srcip", ev.nameinfo.nfexmsg.srcip,
					"desip", ev.nameinfo.nfexmsg.desip, 
					//"protocol", ev.protocol, 
					"protocol", "tcp", 
					//"policynum", ev.policynum, 
					"policynum", "0111", 
					"snapshoot", ev.nameinfo.transformname, 
					"filename", ev.nameinfo.nfexmsg.filename, 
					"fileformat", ev.nameinfo.fileformat, 
					"filepath", BETRANSFORM, 
					//"domain", ev.domain);
					"domain", "www.domain.com");

	fwrite (even, sizeof(char), strlen(even), pf);
	fwrite ("\n", sizeof(char), 1, pf);

	printf ("even=%s\n", even);
	fclose(pf);
	pf = NULL;

	return 0;
}
#endif

int logevent (struct event ev)
{
	//int flag = 1;
	//char even[1024] = {};
	struct mymsg msg;
	//memset(&msg, 0, sizeof(msg));
	int msgid, res;
	
	sprintf (msg.even, "\"event\":[{\"%s\":\"%s\"},{\"%s\":\"%s\", \"%s\":\"%s\", \"%s\":\"%s\", \"%s\":\"%s\", \"%s\":\"%s\", \"%s\":\"%s\", \"%s\":\"%s\", \"%s\":\"%s\", \"%s\":\"%s\"}]", 
					"flag", "1",
					"srcip", ev.nameinfo.nfexmsg.srcip,
					"desip", ev.nameinfo.nfexmsg.desip, 
					//"protocol", ev.protocol, 
					"protocol", "tcp", 
					//"policynum", ev.policynum, 
					"policynum", "0111", 
					"snapshoot", ev.nameinfo.transformname, 
					"filename", ev.nameinfo.nfexmsg.filename, 
					"fileformat", ev.nameinfo.fileformat, 
					"filepath", BETRANSFORM, 
					//"domain", ev.domain);
					"domain", "www.domain.com");

	strcpy (msg.even, "\"event\":[{\"flag\":\"1\"},{\"srcip\":\"192.168.1.13\", \"desip\":\"192.168.1.12\", \"protocol\":\"tcp\", \"policynum\":\"0111\", \"snapshoot\":\"aaa.match\", \"filename\":\"aaa.doc\", \"fileformat\":\"doc\", \"filepath\":\"/root/detector/before_transform\", \"domain\":\"www.domain.com\"}]");
	msgid = msgget(MSGKEY, 0666 | IPC_CREAT);
	res = msgsnd (msgid, &msg, sizeof(msg), 0);
	printf ("even1=%s\n", msg.even);
	//sleep(2);
	//printf ("even2=%s\n", msg.even);
	//msg.mytype = 0;
	//res = msgrcv (msgid, &msg1, sizeof(msg1), 0, 0);
	//printf ("even3=%s\n", msg.even);

	return 0;
}


#if 1
int main()
{
	char *filename = "tang.c";
	char *matchfile = "tang.match";
	//logevent (filename, matchfile);
	struct event ev;
	strcpy(ev.nameinfo.nfexmsg.srcip, "192.168.1.13");
	strcpy(ev.nameinfo.nfexmsg.desip, "192.168.1.12");
	strcpy(ev.protocol, "tcp");
	strcpy(ev.policynum, "1234");
	strcpy(ev.nameinfo.transformname, "aaa.match");
	strcpy(ev.nameinfo.nfexmsg.filename, "aaa.doc");
	strcpy(ev.nameinfo.fileformat, "doc");
	strcpy(ev.filepath, "/root/log");
	strcpy(ev.domain, "domain");

	logevent (ev);
}
#endif
