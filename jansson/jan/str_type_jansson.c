/*
 * Copyright (c) 2009-2013 Petri Lehtinen <petri@digip.org>
 *
 * Jansson is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#include "./str_type_jansson.h"

/* Call the simple functions not covered by other tests of the public API */
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
