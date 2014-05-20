#ifndef MATCHJANS_H_
#define MATCHJANS_H_

#include <stdio.h>
#include <jansson.h>
#include "mydir.h"
#include "event.h"

#define MSGKEY (key_t)0x28a5

struct mymsg
{
	long mytype;
	//char *str;
	char str[1024];
};

int event_jansson(struct event ev, char **janstr);

#endif
