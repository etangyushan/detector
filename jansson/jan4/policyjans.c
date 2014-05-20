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


/* 获取每个元素的值, 返回策略结构体 */
struct policymsg iter_get_value(json_t *object)
{
	struct policymsg policyinfo;
    int i;
    json_t *iter_values[3];
    const char *iter_keys[3];
    void *iter;

#if 0
	printf("判断是不是object类型\n");
	my_json_type(object);
#endif 

    iter = json_object_iter(object);
	i = 0;
	while(1)
	{
		iter_keys[i] = json_object_iter_key(iter);
		iter_values[i] = json_object_iter_value(iter);
		printf("keys[%d]=%s\n", i,iter_keys[i]);
		printf("values[%d]=%s\n", i,json_string_value(iter_values[i]));

		if((iter = json_object_iter_next(object, iter)) == NULL)
		{
			 //printf("iterate end\n");
			 break;
		}
		i++;
	}

#if 1
	i=4;
	iter = json_object_iter_at(object, "b");
    if(iter)
	{
		iter_keys[i] = json_object_iter_key(iter);
		iter_values[i] = json_object_iter_value(iter);
		printf("values[%d]=%s\n", i,json_string_value(iter_values[i]));
        //printf("json_object_iter_at() printfs for an existing key\n");
	}
#endif

    json_decref(object);
	return policyinfo;
}

/* 得到策略信息 */
struct policymsg get_policy_json(char *jsonfile)
{
	json_t *object;
	json_error_t error;
	int res;
	struct policymsg policyinfo;

	object = json_object();

	/* 读取策略 */
	object = json_load_file (jsonfile, 0, &error);

#if 0
	/* 取出object中的值 */
	//struct policy iter_get_value(json_t *object)
	char *result;
    result = json_dumps(object, JSON_PRESERVE_ORDER);
	printf("result=%s\n", result);
	/* 判断读取的jansson类型 */
	my_json_type(object);
	printf("size = %d\n", strlen(result));
#endif

	printf("得到策略值\n");
	policyinfo = iter_get_value(object);
	return  policyinfo;
}

#if 1
int main()
{	

//result = "{\"objectmsg\": \"{\"name1\": \"value1\", \"name2\": \"value2\", \"name3\": \"value3\", \"name4\": \"value4\"}\", \"name5\": \"value6\"}";
#if 0
	//char *str = "./tmp.json";
	struct policymsg p;
	json_t *object;
	object = json_object();
#endif
	char *str = "./tmp.json";
	get_policy_json(str);
}
#endif
