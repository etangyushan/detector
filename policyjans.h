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
/* keywordbuf对应着detail相同下标的策略条件, 
 * 例如: 
 *  	keywordbuf[0] = "ok" detail[0]=5 代表了 ok匹配的次数是5次 
 **/
struct policymsg
{
	int size;
	char keyword[COUNTMAX][LENMAX];
	char keycount[COUNTMAX][LENMAX];
	char flag[COUNTMAX][LENMAX];
};

/* 判断janson的类型 */
int my_json_type(json_t *value);

/* 得到策略信息 */
struct policymsg get_policy_json(char *jsonfile);

#endif
