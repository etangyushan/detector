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

/* 得到策略信息 */
struct policymsg get_policy_json(char *jsonfile)
{
	struct policymsg policyinfo;
	int i, size;
    void *iter;
	json_t *object;
    json_t *iter_values;
	json_error_t error;

	object = json_object();
	/* 读取策略 */
	object = json_load_file (jsonfile, 0, &error);
	policyinfo.size = json_object_size (object);
#if 0
	//size = json_object_size (object);
	//printf("size=%d\n", size);
	/* 取出object中的值 */
	//struct policy iter_get_value(json_t *object)
	char *result;
    result = json_dumps(object, JSON_PRESERVE_ORDER);
	printf("result=%s\n", result);
	/* 判断读取的jansson类型 */
	printf("判断是什么类型\n");
	my_json_type(object);
	printf("result_size = %d\n", strlen(result));
#endif

	//printf("得到策略值\n");
    iter = json_object_iter(object);
	i = 0;
	while(1)
	{
		strcpy (policyinfo.keyword[i], json_object_iter_key(iter));
		iter_values = json_object_iter_value(iter);
		strcpy (policyinfo.keycount[i],json_string_value(iter_values));

		//printf("values[%d]=%s\n", i,json_string_value(iter_values[i]));

		if((iter = json_object_iter_next(object, iter)) == NULL)
		{
			 //printf("iterate end\n");
			 break;
		}
		i++;
	}

#if 0
	iter = json_object_iter_at(object, "b");
    if(iter)
	{
		iter_keys[i] = json_object_iter_key(iter);
		iter_values[i] = json_object_iter_value(iter);
		printf("values[%d]=%s\n", i,json_string_value(iter_values[i]));
	}
#endif

    json_decref(object);
	return policyinfo;
}

#if 1
int main()
{	

	//result = "{\"objectmsg\": \"{\"name1\": \"value1\", \"name2\": \"value2\", \"name3\": \"value3\", \"name4\": \"value4\"}\", \"name5\": \"value6\"}";
	char *str = "./tmp.json";
	struct policymsg policyinfo;
	policyinfo = get_policy_json(str);
	int i = 0;

	while ( i < policyinfo.size)
	{
		printf ("keyword = %s\n", policyinfo.keyword[i]);
		printf ("value = %s\n", policyinfo.keycount[i]);
		i++;
	}
}
#endif
