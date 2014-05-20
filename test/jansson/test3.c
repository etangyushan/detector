#include <stdio.h>
#include <jansson.h>

int event_jansson(struct event ev)
{
	json_t *name1;	
	json_t *name2;	
	json_t *name3;	
	json_t *name4;	
	json_t *name5;	
	json_t *name6;	
	json_t *name7;	
	json_t *name8;	
	json_t *name9;	
	json_t *name10;	
	json_t *name11;
	json_t *name12;
	json_t *tmp;
	json_t *objectmsg;
	json_t *objectall;
	const char *str;
	int res;

	printf ("字符串string测试...\n");
	/* jsonStr */
	name1 = json_string ("jsonStr");
	str = json_string_value (name1);
	printf ("str=%s\n", str);

	/* incID */
	name2 = json_string ("incID");
	str = json_string_value (name2);
	printf ("str=%s\n", str);


	/* srcip */
	name3 = json_string (ev.nameinfo.srcip);
	str = json_string_value (name3);
	printf ("str=%s\n", str);

	/* desip */
	name4 = json_string (ev.nameinfo.desip);
	str = json_string_value (name4);
	printf ("str=%s\n", str);

	/* protocol */
	name5 = json_string ("protocol-tcp");
	str = json_string_value (name5);
	printf ("str=%s\n", str);

	/* policyID */
	name6 = json_string ("policyID-1111");
	str = json_string_value (name6);
	printf ("str=%s\n", str);

	/* snapshot */
	name7 = json_string (ev.nameinfo.snapshot);
	str = json_string_value (name7);
	printf ("str=%s\n", str);

	/* filename */
	name8 = json_string (ev.nameinfo.filename);
	str = json_string_value (name8);
	printf ("str=%s\n", str);

	/* fileType */
	name9 = json_string (ev.nameinfo.fileformat);
	str = json_string_value (name9);
	printf ("str=%s\n", str);

	/* filePath */
	name10 = json_string (BETRANSFROM);
	str = json_string_value (name10);
	printf ("str=%s\n", str);

	/* domain */
	name11 = json_string ("www.domain.com");
	str = json_string_value (name11);
	printf ("str=%s\n", str);

	/* commandKey */
	name12 = json_string ("10101010");
	str = json_string_value (name12);
	printf ("str=%s\n", str);

	printf ("对象object测试...\n");
	objectmsg = json_object();	
	objectall = json_object();	
	//size_t size = json_object_size (object);
	
	json_object_set (objectmsg, "incID", name2);
	//json_object_set (objectmsg, "incID", name2);
	json_object_set (objectmsg, "srcip", name3);
	//json_object_set (objectmsg, ev.nameinfo.srcip, name3);
	json_object_set (objectmsg, "desip", name4);
	//json_object_set (objectmsg, ev.nameinfo.desip, name4);
	json_object_set (objectmsg, "protocol", name5);
	//json_object_set (objectmsg, "tcp", name5);
	json_object_set (objectmsg, "policyID", name6);
	//json_object_set (objectmsg, "111", name6);
	json_object_set (objectmsg, "snapshot", name7);
	//json_object_set (objectmsg, ev.nameinfo.snapshot, name7);
	json_object_set (objectmsg, "filename", name8);
	//json_object_set (objectmsg, ev.nameinfo.filename, name8);
	json_object_set (objectmsg, "fileType", name9);
	//json_object_set (objectmsg, ev.nameinfo.fileformat, name9);
	json_object_set (objectmsg, "filePath", name10);
	//json_object_set (objectmsg, BETRANSFROM, name10);
	json_object_set (objectmsg, "domain", name11);
	//json_object_set (objectmsg, "www.domain.com", name11);
	json_object_set (objectall, "jsonStr", objectmsg);
	//json_object_set (objectall, "jsonStr", objectmsg);
	json_object_set (objectall, "commandKey", name12);
	//json_object_set (objectall, "commandKey", name12);

	char *str2 = json_dumps(objectall, 11);
	printf ("str=%s\n", str2);
}

int main()
{	
	struct event ev;

	event_jansson(ev);
}
