#ifndef POLICYJANS_H_
#define POLICYJANS_H_

#include <jansson.h>
#include <string.h>
#include <string.h>
#include <jansson.h>
#include <stdio.h>
#include <jansson.h>
//#include "mydir.h"
//#include "event.h"

/* 关键字个数 */
#define COUNTMAX  256
/* 关键字长度 */
#define LENMAX 256
/* keywordbuf对应着detail相同下标的策略条件, keywordbuf[0] = "ok" detail[0]=5 代表了 ok匹配的次数是5次 */
struct policymsg
{
	char keyword[COUNTMAX][LENMAX];
	char detail[COUNTMAX];
};

int event_jansson();
//int event_jansson(struct event ev, char **janstr);
//int event_jansson(struct event ev, char **janstr);


/* Call the simple functions not covered by other tests of the public API */
int my_json_type(json_t *value);


/* 获取每个元素的值, 返回元素的结构体 */
struct policymsg iter_get_value(json_t *object);


#endif
