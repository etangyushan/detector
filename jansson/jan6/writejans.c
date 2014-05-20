
#include "./policyjans.h"

int event_jansson()
{

	printf ("产生json格式数据......\n");
	json_t *objectmsg;
	json_t *objectall;
	json_t *tmp;
	char *result;
	int res;
	char *str = "./tmp.json";
#if 1

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
#if 0
	tmp = json_string (result);
	result = NULL;
	json_object_set_new (objectall, "objectmsg", tmp);
	json_object_set_new (objectall, "name5", json_string("value5"));
    result = json_dumps(objectall, JSON_PRESERVE_ORDER);
    free(result);
	json_decref(tmp);
#endif
	FILE *pf = fopen(str, "w");
	fwrite(result, sizeof(char), strlen(result), pf);
	fclose(pf);
	pf = NULL;
	printf("result=%s\n", result);

	free(result);
    json_decref(objectmsg);
    //json_decref(objectall);

#endif

	/* 以上程序得出的json格式字符串 */
	//result = "{\"objectmsg\": \"{\"name1\": \"value1\", \"name2\": \"value2\", \"name3\": \"value3\", \"name4\": \"value4\"}\", \"name5\": \"value6\"}";

#if 0
	//char *str = "{\"name\":\"key\"}"; 
	json_t *object;
	object = json_object();
	//printf("------my_json_type1------\n");
	res = my_json_type(object);
	//printf("------my_json_type2------\n");
	//printf("size = %d\n", strlen(result));
	json_error_t error;
	/* 读取策略 */
	//object = json_loads (str, strlen(str), &error);
	
	//object = json_load_file (str, strlen(str), &error);
	object = json_load_file (str, 0, &error);
	/* 取出object中的值 */
	//struct policy iter_get_value(json_t *object)
	/* 判断读取的jansson类型 */

	res = my_json_type(object);

	printf("得到值\n");
	iter_get_value(object);
	
    result = json_dumps(object, JSON_PRESERVE_ORDER);
	printf("result=%s\n", result);
#endif

}

#if 1
int main()
{	

#if 0
	struct policy p;
	json_t *object;
	object = json_object();
	p = iter_get_value(object);
#endif

	event_jansson();
}
#endif
