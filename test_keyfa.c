#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

//#define KEYVALUE (key_t)0x4fff
#define KEYVALUE (key_t)0x27dc

struct msgkey
{
	long mytype;
	char keybuf[256];
};

int
main ()
{
	struct msgkey keyinfo;
	int msgid, res;
	strcpy (keyinfo.keybuf, "a");

	keyinfo.mytype = 1;
	msgid = msgget (KEYVALUE, 0666 | IPC_CREAT);
	if (msgid == -1) {
		perror ("msgget");
	}
	res = msgsnd (msgid, &keyinfo, sizeof (keyinfo.keybuf), 0);
	if (res == -1) {
		perror ("msgsnd");
	}
}
