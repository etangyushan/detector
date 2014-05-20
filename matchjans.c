#include "./matchjans.h"

int
event_jansson (struct event ev, char **janstr)
{
	printf ("产生json格式数据......\n");
	json_t *objectmsg;
	json_t *objectall;
	json_t *tmp;
	char *result;
	char *str2 = *janstr;
	struct mymsg msg;
	int msgid, res;

	//printf ("对象object测试...\n");
	objectmsg = json_object ();
	objectall = json_object ();

	json_object_set_new (objectmsg, "incID", json_string ("incID"));
	json_object_set_new (objectmsg, "srcip", json_string (ev.nameinfo.srcip));
	json_object_set_new (objectmsg, "desip", json_string (ev.nameinfo.desip));
	json_object_set_new (objectmsg, "protocol", json_string ("protocol-tcp"));
	json_object_set_new (objectmsg, "policyID", json_string ("policyID-1111"));
	json_object_set_new (objectmsg, "snapshot", json_string (ev.nameinfo.snapshot));
	json_object_set_new (objectmsg, "filename", json_string (ev.nameinfo.filename));
	json_object_set_new (objectmsg, "fileType", json_string (ev.nameinfo.fileformat));
	json_object_set_new (objectmsg, "filePath", json_string (BETRANSFORM));
	json_object_set_new (objectmsg, "domain", json_string ("www.domain.com"));

	result = json_dumps (objectmsg, JSON_PRESERVE_ORDER);
	tmp = json_string (result);
	free (result);
	result = NULL;
	json_object_set_new (objectall, "message", tmp);
	json_object_set_new (objectall, "commandType", json_string ("10101010"));
	result = json_dumps (objectall, JSON_PRESERVE_ORDER);

#if 1
	msg.mytype = 1;
	strcpy (msg.str, result);
	//strcpy(msg.str, "1111111");
	msgid = msgget (MSGKEY, 0666 | IPC_CREAT);
	res = msgsnd (msgid, &msg, sizeof (msg.str), 0);
	printf ("发送的json格式字符串: %s\n", msg.str);
#endif

	free (result);
	json_decref (objectmsg);
	json_decref (objectall);
}

#if 0
int
main ()
{
	struct event ev;
	char *str;
	event_jansson (ev, &str);
}
#endif
