/*
 * Copyright (c) 2009-2013 Petri Lehtinen <petri@digip.org>
 *
 * Jansson is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#include "./object_iter_jansson.h"
//#include "./str_type_jansson.h"

/* 获取每个元素的值, 返回元素的结构体 */
struct policy iter_get_value(json_t *object)
{
	struct policy p;
    int i;
    json_t *iter_values[3];
    const char *iter_keys[3];
    void *iter;

	printf("判断是不是object类型\n");
	my_json_type(object);
	printf("........\n");
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
		printf("values[%d]=%s\n", i,json_string_value(iter_values[i]));

		if((iter = json_object_iter_next(object, iter)) == NULL)
		{
			 printf("iterate end\n");
			 break;
		}
		i++;
	}

	iter = json_object_iter_at(object, "b");
    if(iter)
	{
		iter_keys[i] = json_object_iter_key(iter);
		iter_values[i] = json_object_iter_value(iter);
		printf("values[%d]=%s\n", i,json_string_value(iter_values[i]));
        printf("json_object_iter_at() printfs for an existing key\n");
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

#if 0
int main()
{
	struct policy p;
	json_t *object;
	object = json_object();
	p = iter_get_value(object);
	return 0;
}
#endif 
