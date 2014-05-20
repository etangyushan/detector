#include "./ssl_client.h"
#include "./mydir.h"
#include "./filenamelog.h"

#define MSGLENGTH 1024
/* nfex通信 */
#define MATCHVALUE (key_t)0x1fff
/* 两个线程间通信 */
#define SEEKVALUE (key_t)0x2fff
//#define KEYVALUE (key_t)0x4fff
#define KEYVALUE (key_t)0x27dc
//#define SEEKVALUE2 (key_t)0x3fff
//#define NETDEV "em1"
#define NETDEV "eth1"

pthread_mutex_t lockmatch;
pthread_mutex_t locktransform;

struct msgkey keyinfo;

int tag = 0;
/*  如果结束修改tag为1 */
void
fa (int signal)
{
	tag = 1;
	printf ("程序退出......\n");
	exit (-1);
}

/* 转换文件线程 */
void *
transform_file_pthread (void *p)
{
	printf ("转换文件线程开始...\n");
	int msgid1, msgid2, res;
	char command[256] = { };
	struct msgtransform msg;
	int i = 2;
	//while (i--)
	while (1) {
		if (tag == 1) {
			break;
		}
		/* 检查消息队列,获取nfex消息 */
		printf ("等待nfex发送消息...\n");
		//msg.mytype = 1;
		msgid1 = msgget (MATCHVALUE, 0666 | IPC_CREAT);
		if (msgid1 == -1) {
			perror ("msgget-ssl_client.c-57");
		}
		//res = msgrcv (msgid, &(nameinfo.nfexmsg), sizeof(nameinfo.nfexmsg), 0, 0);
		res = msgrcv (msgid1, &(msg), sizeof (msg), 0, 0);
		if (res == -1) {
			perror ("ssl_client.c-47-msgrcv");
		}
		else {
			printf ("收到nfex消息......\n");
#if 0
			printf ("nfexmg.srcip=%s\n", msg.nameinfo.srcip);
			printf ("nfexmg.desip=%s\n", msg.nameinfo.desip);
			printf ("nfexmg.filename=%s\n", msg.nameinfo.filename);
			printf ("namemsg.transformname=%s\n", msg.nameinfo.transformname);
			printf ("namemsg.fileformat=%s\n", msg.nameinfo.fileformat);
#endif
			/* 根据记录文件进行转换 */
			//printf ("进行转换\n");
#if 1
			for (i = 0; i < 5; i++) ;
			{
				sleep (1);
			}
#endif
			printf ("开始转换文件......\n");
			pthread_mutex_lock (&locktransform);
			filetotxt (&msg.nameinfo);
			pthread_mutex_unlock (&locktransform);
			printf ("转换文件完成......\n");

#if 0
			printf ("nfexmg.srcip=%s\n", nameinfo->nfexmsg.srcip);
			printf ("nfexmg.desip=%s\n", nameinfo->nfexmsg.desip);
			printf ("nfexmg.filename=%s\n", nameinfo->nfexmsg.filename);
			printf ("namemsg.transformname=%s\n", nameinfo->transformname);
			printf ("namemsg.fileformat=%s\n", nameinfo->fileformat);
#endif
			//printf ("进行转换2\n");

			/* 发送消息队列给匹配线程 */
#if 1
			pthread_mutex_lock (&locktransform);
			printf ("发送消息给匹配线程......\n");
			msg.mytype = 2;
			msgid2 = msgget (SEEKVALUE, 0666 | IPC_CREAT);
			//res = msgsnd (msgid2, &nameinfo, sizeof(struct namemsg), 0);
			res = msgsnd (msgid2, &msg, sizeof (msg), 0);
			if (res == -1) {
				perror ("ssl_client.c-64-msgsnd");
			}
			pthread_mutex_unlock (&locktransform);
#endif
		}
#if 0
		printf ("删除消息对列......\n");
		res = msgctl (msgid1, IPC_RMID, 0);
		if (res == -1) {
			perror ("ssl_client.c-118-msgmsgctl");
		}
#endif
	}

	printf ("转换文件线程结束...\n");
	pthread_exit ((void *)1);
}

/* 匹配文件线程 */
void *
match_file_pthread (void *p)
{
	printf ("匹配文件线程开始...\n");

	int msgid, res;
	struct msgtransform msg;
	//char msg[256] = {};
	char keybuf[1024] = { };
	while (1) {
		if (tag == 1) {
			break;
		}
		/* 等待消息队列 */
		printf ("等待转换线程消息...\n");
#if 1
		pthread_mutex_lock (&lockmatch);
		msg.mytype = 2;
		msgid = msgget (SEEKVALUE, 0666 | IPC_CREAT);
		//res = msgrcv (msgid, &nameinfo, sizeof(struct namemsg), 0, 0);
		res = msgrcv (msgid, &msg, sizeof (msg), 0, 0);
		if (res == -1) {
			perror ("msgrcv-190");
		}
		else {
#if 0
			printf ("2-nfexmg.srcip=%s\n", msg.nameinfo.srcip);
			printf ("2-nfexmg.desip=%s\n", msg.nameinfo.desip);
			printf ("2-nfexmg.filename=%s\n", msg.nameinfo.filename);
			printf ("2-namemsg.transformname=%s\n", msg.nameinfo.transformname);
			printf ("2-namemsg.fileformat=%s\n", msg.nameinfo.fileformat);
#endif
			/* 调用匹配函数，将匹配目录下的所有文件 */
			printf ("接收到转换线程消息...开始匹配...\n");

#if 0
			/* 接收关键字的消息队列 */
			//struct msgkey keyinfo;
			keyinfo.mytype = 1;
			msgid = msgget (KEYVALUE, 0666 | IPC_CREAT);
			if (res == -1) {
				perror ("msgget");
			}
			//strcpy(keyinfo.keybuf, "a");

			res = msgrcv (msgid, &keyinfo, sizeof (keyinfo.keybuf), 0, 0);
			if (res == -1) {
				perror ("msgrcv");
			}
			//res = matchfile (msg.nameinfo, KEYWORDSTR);
#endif
			strcpy (keybuf, keyinfo.keybuf);
			//res = matchfile (msg.nameinfo, keyinfo.keybuf);
			res = matchfile (msg.nameinfo, keybuf);

			printf ("匹配完成......\n");
		}
#if 0
		printf ("删除消息队列......\n");
		res = msgctl (msgid, IPC_RMID, 0);
		if (res == -1) {
			perror ("msgctl-ssl_client.c-175");
		}
#endif
		pthread_mutex_unlock (&lockmatch);
#endif
	}

	printf ("匹配文件线程结束...\n");
	pthread_exit ((void *)1);
}

/* 计算机状态线程 */
void *
computerstate_pthread (void *p)
{
	info_ma data;
	char buf[256] = { };
	char msg[1024] = { };
	char *filename = COMPUTERSTATE;
	FILE *fp = fopen (filename, "w");

	while (1) {
		if (tag == 1) {
			break;
		}
		//data = computerstate(NULL);
		/* 默认空为eth0 */
		data = computerstate (NETDEV);
		sprintf (buf, "memory:%0.2f%%, cpu:%0.2f%%, disk:%0.2%%lf, upload:%0.2fk/s, download:%0.2fk/s", data.memory, 100 - data.cpu, data.disk, data.put, data.get);
		sprintf (msg, "{\"%s\":\"%s\"}\n", "computerstate", buf);
		fwrite (msg, sizeof (char), strlen (msg), fp);
	}

	fclose (fp);
	fp = NULL;
	pthread_exit ((void *)1);
}

/* 接收关键字的线程 */
void *
keyword_pthread (void *p)
{
	printf ("接收关键字线程开始......\n");
	int msgid, res;
	char buf[1024] = { };
	//struct msgkey keyinfo;
	keyinfo.mytype = 1;
	msgid = msgget (KEYVALUE, 0666 | IPC_CREAT);
	if (res == -1) {
		perror ("msgget");
	}
	while (1) {
		//strcpy(keyinfo.keybuf, "a");
		//memset (buf, 0, sizeof(buf));         
		//res = strlen(keyinfo.keybuf);
		//strncpy(buf, keyinfo.keybuf, res);
		res = msgrcv (msgid, &keyinfo, sizeof (keyinfo.keybuf), 0, 0);
		if (res == -1) {
			perror ("msgrcv");
		}
		printf ("收到的关键字=%s\n", keyinfo.keybuf);
	}
	printf ("接收关键字线程结束......\n");
	pthread_exit ((void *)1);
}

int
main ()
{
	printf ("客户端启动...\n");
	/* 注册自定义信号函数 */
	signal (SIGINT, fa);

	pthread_mutex_init (&locktransform, 0);
	pthread_mutex_init (&lockmatch, 0);

	/* 创建接收https线程，发送到https线程,发送到sftp线程,匹配文件线程 */
	pthread_t id0, id1, id2, id3, id4, id5, id6, id7, id8;

	/* 接收关键字 */
	pthread_create (&id0, 0, keyword_pthread, 0);
	/* 创建转换文件线程 */
	pthread_create (&id1, 0, transform_file_pthread, 0);

	/* 创建匹配文件线程 */
	pthread_create (&id2, 0, match_file_pthread, 0);

	/* 创建计算机状态线程 */
	pthread_create (&id3, 0, computerstate_pthread, 0);
#if 0
	pid_t pid = fork ();
	if (pid == 0) {

		computerstate_pthread (NULL);
	}
#endif

	pthread_join (id0, 0);
	pthread_join (id1, 0);
	pthread_join (id2, 0);
	pthread_join (id3, 0);
	pthread_mutex_destroy (&locktransform);
	pthread_mutex_destroy (&lockmatch);
	//pthread_join (id4, 0);
	DEBUG ("客户端关闭...\n");
	return 0;
}
