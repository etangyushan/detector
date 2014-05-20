#ifndef JANS_H_
#define JANS_H_

#include <stdio.h>
#include <jansson.h>
//#include "mydir.h"
//#include "event.h"
#include "./str_type_jansson.h"
#include "./object_iter_jansson.h"

/* 关键字个数 */
#define COUNTMAX  256
/* 关键字长度 */
#define LENMAX 256
struct policy
{
	char keywordbuf[COUNTMAX][LENMAX];
};


int event_jansson();
//int event_jansson(struct event ev, char **janstr);
//int event_jansson(struct event ev, char **janstr);

#endif
