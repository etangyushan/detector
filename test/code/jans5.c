/*
 * Copyright (c) 2009-2013 Petri Lehtinen <petri@digip.org>
 *
 * Jansson is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#include "./jans.h"
#define MSGKEY (key_t)0x28a2
struct mymsg
{
	long mytype;
	char even[1024];
};


int event_jansson(struct event ev, char **janstr)
{
    json_t *objectmsg;
    json_t *objectall;
    char *result;
	struct mymsg msg;
	int msgid, res;

    objectmsg = json_object();
	objectall = json_object();

	json_object_set_new (objectmsg, "incID", json_string("incID"));
	json_object_set_new (objectmsg, "srcip", json_string(ev.nameinfo.srcip));
	json_object_set_new (objectmsg, "desip", json_string(ev.nameinfo.desip));
	json_object_set_new (objectmsg, "protocol", json_string("protocol-tcp"));
	json_object_set_new (objectmsg, "policyID", json_string("policyID-1111"));
	json_object_set_new (objectmsg, "snapshot", json_string(ev.nameinfo.snapshot));
	json_object_set_new (objectmsg, "filename", json_string(ev.nameinfo.filename));
	json_object_set_new (objectmsg, "fileType", json_string(ev.nameinfo.fileformat));
	json_object_set_new (objectmsg, "filePath", json_string(BETRANSFORM));
	json_object_set_new (objectmsg, "domain", json_string("www.domain.com"));

#if 0
	json_object_set_new (objectmsg, "incID", json_string("value-incID"));
	json_object_set_new (objectmsg, "srcip", json_string("a"));
	json_object_set_new (objectmsg, "desip", json_string("b"));
	json_object_set_new (objectmsg, "protocol", json_string("bc"));
	json_object_set_new (objectmsg, "policyID", json_string("bc"));
	json_object_set_new (objectmsg, "snapshot", json_string("bc"));
	json_object_set_new (objectmsg, "filename", json_string("bc"));
	json_object_set_new (objectmsg, "fileType", json_string("bc"));
	json_object_set_new (objectmsg, "filePath", json_string("bc"));
	json_object_set_new (objectmsg, "domain", json_string("bc"));
#endif
    result = json_dumps(objectmsg, JSON_PRESERVE_ORDER);
	json_t *ss = json_string (result);
    free(result);
	result = NULL;
	json_object_set_new (objectall, "jsonStr", ss);
	json_object_set_new (objectall, "commandKey", json_string("10101010"));
    result = json_dumps(objectall, JSON_PRESERVE_ORDER);

	//printf("result=%s\n",result);
	printf ("发送的json格式字符串: %s\n", msg.even);
	msg.mytype = 1;
	strcpy(msg.even, result);
	msgid = msgget(MSGKEY, 0666 | IPC_CREAT);
	res = msgsnd (msgid, &msg, sizeof(msg), 0);

    free(result);
    json_decref(objectmsg);
    json_decref(objectall);
}

#if 0
int main() {
	int res;
	struct event ev;
	char *janstr;
	while(1)
	res = event_jansson(ev, &janstr);
    return 0;
}
#endif

