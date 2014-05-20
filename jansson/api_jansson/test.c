#include <stdio.h>
#include <jansson.h>

int main()
{
	json_t *name;	
	json_t *tmp;
	json_t *object;
	json_t *array;
	json_t *name2;

	int res;

	printf ("字符串string测试...\n");
	name = json_string ("name");
	res = json_string_set (name, "tang");
	const char *str = json_string_value (name);
	printf ("str=%s\n", str);

	printf ("整数integer测试...\n");
	json_int_t num = 123456;
	name2 = json_integer (num);
	json_integer_set (name2, 654321);
	json_int_t renum = json_integer_value (name2);
	printf("renum=%d\n", renum);


	printf ("数组array测试...\n");
	array = json_array();
	//size_t ret = json_array_size (array);
	//printf ("size=%d\n", ret);
	//res = json_array_set (array, 0, name);
	res = json_array_append (array, name);
	res = json_array_append (array, name2);

	tmp = json_array_get (array, 0);
	if(tmp)
	{
		const char *str2 = json_string_value (tmp);
		printf ("str2=%s\n", str2);
	}
	tmp = json_array_get (array, 1);
	if (tmp)
	{
		json_int_t renum = json_integer_value (name2);
		printf("renum=%d\n", renum);
	}

	printf ("对象object测试...\n");
	object = json_object();	
	//size_t size = json_object_size (object);
	json_object_set (object, "key", array);
	size_t ret = json_array_size (array);
	printf ("size=%d\n", ret);
	tmp = json_object_get (object, "key");
	const char *objstr = json_string_value (tmp);
	printf ("objstr=%s\n", objstr);

}
