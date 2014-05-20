#include <stdio.h>
#include <jansson.h>

int main()
{
	json_t *name;	
	json_t *tmp;
	json_t *objectmsg;
	json_t *objectall;
	const char *str;
	int res;

	printf ("字符串string测试...\n");
	name = json_string ("jsonStr");
	str = json_string_value (name);
	printf ("str=%s\n", str);
	//res = json_string_set (name, "1");
	//str = json_string_value (name);
	//printf ("str=%s\n", str);

	objectall = json_object();	
	//size_t size = json_object_size (object);
	json_object_set (objectall, "jsonStr", name);
	json_object_set (objectall, "jsonStr2", name);
	char *str2 = json_dumps(objectall, 2);
	printf ("str=%s\n", str2);

	
}
