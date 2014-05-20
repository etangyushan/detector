/*
 * Copyright (c) 2009-2013 Petri Lehtinen <petri@digip.org>
 *
 * Jansson is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */
#ifndef OBJECT_ITER_JANSSON_H
#define OBJECT_ITER_JANSSON_H

#include <jansson.h>
#include <string.h>
#include "./get_jans.h"

/* 获取每个元素的值, 返回元素的结构体 */
struct policy iter_get_value(json_t *object);

#endif
