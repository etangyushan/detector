/*
 * Copyright (c) 2009-2013 Petri Lehtinen <petri@digip.org>
 *
 * Jansson is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#include "./policyjans.h"


/* 判断janson的类型 */
int my_json_type(json_t *value)
{
    if(json_is_object(value))
	{
        printf("json_is_object\n");
		return JSON_OBJECT;
	}

    if(json_is_array(value))
	{
        printf("json_is_array\n");
		return JSON_ARRAY;
	}

    if(json_is_string(value))
	{
        printf("json_is_string\n");
		return JSON_STRING;
	}

    if(json_is_integer(value))
	{
        printf("json_is_integer\n");
		return JSON_INTEGER;
	}

    if(json_is_real(value))
	{
        printf("json_is_real\n");
		return JSON_REAL;
	}

    if(json_is_number(value))
	{
        printf("json_is_number\n");
	}

    if(json_is_boolean(value))
	{
        printf("json_is_boolean\n");
	}

    if(json_is_null(value))
	{
        printf("json_is_null\n");
		return JSON_NULL;
	}

	if(json_is_true(value))
	{
        printf("json_boolean(1)\n");
		return JSON_TRUE;
	}

    if(json_is_false(value))
	{
        printf("json_boolean(0)\n");
		return JSON_FALSE;
	}
}


/* 获取每个元素的值, 返回元素的结构体 */
struct policymsg iter_get_value(json_t *object)
{
	struct policymsg p;
    int i;
    json_t *iter_values[3];
    const char *iter_keys[3];
    void *iter;

	printf("判断是不是object类型\n");
	my_json_type(object);
	//printf("........\n");
#if 0
    if(json_object_iter(NULL))
	{
        printf("iterate NULL\n");
	}

    if(json_object_iter_next(NULL, NULL))
	{
        printf("iterator a NULL object\n");
	}
#endif 

    iter = json_object_iter(object);
	i = 0;
	while(1)
	{
		iter_keys[i] = json_object_iter_key(iter);
		iter_values[i] = json_object_iter_value(iter);
		//printf("values[%d]=%s\n", i,json_string_value(iter_values[i]));

		if((iter = json_object_iter_next(object, iter)) == NULL)
		{
			 //printf("iterate end\n");
			 break;
		}
		i++;
	}

	i=4;
	iter = json_object_iter_at(object, "b");
    if(iter)
	{
		iter_keys[i] = json_object_iter_key(iter);
		iter_values[i] = json_object_iter_value(iter);
		printf("values[%d]=%s\n", i,json_string_value(iter_values[i]));
        //printf("json_object_iter_at() printfs for an existing key\n");
	}

#if 0
    if(json_object_iter_set(object, iter, baz))
        printf("unable to set value at iterator");

    if(strcmp(json_object_iter_key(iter), "b"))
        printf("json_object_iter_key() printfs after json_object_iter_set()");
    if(json_object_iter_value(iter) != baz)
        printf("json_object_iter_value() printfs after json_object_iter_set()");
    if(json_object_get(object, "b") != baz)
        printf("json_object_get() printfs after json_object_iter_set()");
#endif

    json_decref(object);
	return p;
}

int event_jansson()
{

	printf ("产生json格式数据......\n");
	json_t *objectmsg;
	json_t *objectall;
	json_t *tmp;
	char *result;
	int res;
	char *str = "./tmp.json";
#if 0

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

	FILE *pf = fopen(str, "w");
	fwrite(result, sizeof(char), strlen(result), pf);
	fclose(pf);
	pf = NULL;
	json_decref(tmp);
	printf("result=%s\n", result);

	free(result);
    json_decref(objectmsg);
    json_decref(objectall);

#endif

	/* 以上程序得出的json格式字符串 */
	//result = "{\"objectmsg\": \"{\"name1\": \"value1\", \"name2\": \"value2\", \"name3\": \"value3\", \"name4\": \"value4\"}\", \"name5\": \"value6\"}";

#if 1
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

	//printf("------my_json_type1------\n");
	res = my_json_type(object);
	//printf("------my_json_type2------\n");

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
