#ifndef STR_TYPE_JANSSON_H_
#define STR_TYPE_JANSSON_H_
/*
 * Copyright (c) 2009-2013 Petri Lehtinen <petri@digip.org>
 *
 * Jansson is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#include <string.h>
#include <jansson.h>

/* Call the simple functions not covered by other tests of the public API */
int my_json_type(json_t *value);

#endif
