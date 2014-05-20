#include <stdio.h>
#include <string.h>
#include <jansson.h>
#include "./str_type_jansson.h"

int event_jansson()
{

	printf ("产生json格式数据......\n");
	json_t *objectmsg;
	json_t *objectall;
	json_t *tmp;
	char *result;

	//printf ("对象object测试...\n");
	objectmsg = json_object();	
	objectall = json_object();	

	/* 得到一个json格式的字符串 */
	json_object_set_new (objectmsg, "name1", json_string("value1"));
	json_object_set_new (objectmsg, "name2", json_string("value2"));
	json_t *name3 = json_string("value3");
	json_t *name4 = json_string("value4");
	json_object_set_new (objectmsg, "name3", name3); 
	json_object_set_new (objectmsg, "name4", name4); 

	result = json_dumps(objectmsg, JSON_PRESERVE_ORDER);
	tmp = json_string (result);
    free(result);
	result = NULL;
	json_object_set_new (objectall, "objectmsg", tmp);
	json_object_set_new (objectall, "name5", json_string("value6"));
    result = json_dumps(objectall, JSON_PRESERVE_ORDER);

	FILE *pf = fopen("str.json", "w");
	fwrite(result, sizeof(char), strlen(result), pf);
	fclose(pf);
	pf = NULL;
	json_decref(tmp);
	printf("result=%s\n", result);

	/* 以上程序得出的json格式字符串 */
	//result = "{\"objectmsg\": \"{\"name1\": \"value1\", \"name2\": \"value2\", \"name3\": \"value3\", \"name4\": \"value4\"}\", \"name5\": \"value6\"}";

	free(result);
    json_decref(objectmsg);
    json_decref(objectall);
}

int main()
{	
	event_jansson();
}
