#include "./ssl_client.h"
#include "./mydir.h"
#include "./filenamelog.h"

#define MSGLENGTH 1024
#define MATCHVALUE (key_t)0x1fff
#define SEEKVALUE (key_t)0x2fff

int tag = 0;

/*  如果结束修改tag为1 */
void fa (int signal)
{
	tag = 1;
}


#define BUFFER_SIZE 2 // 缓冲区数量

struct prodcons
{
	// 缓冲区相关数据结构
	//struct namemsg *nameinfo = (struct namemsg*)malloc(sizeof(struct namemsg));
	//memset (nameinfo, 0, sizeof(struct namemsg));
	struct namemsg nameinfo[BUFFER_SIZE]; /* 实际数据存放的数组*/
	pthread_mutex_t lock; /* 互斥体lock 用于对缓冲区的互斥操作 */
	int readpos, writepos; /* 读写指针*/
	pthread_cond_t notempty; /* 缓冲区非空的条件变量 */
	pthread_cond_t notfull; /* 缓冲区未满的条件变量 */
};

/* 初始化缓冲区结构 */
void init(struct prodcons *b)
{
	pthread_mutex_init(&b->lock, NULL);
	pthread_cond_init(&b->notempty, NULL);
	pthread_cond_init(&b->notfull, NULL);
	b->readpos = 0;
	b->writepos = 0;
}

/* 将产品放入缓冲区,这里是存入一个结构体*/
void put(struct prodcons *b, struct namemsg data)
{
	pthread_mutex_lock(&b->lock);

	/* 等待缓冲区未满*/
	if ((b->writepos + 1) % BUFFER_SIZE == b->readpos)
	{
		pthread_cond_wait(&b->notfull, &b->lock);
	}
	/* 写数据,并移动指针 */
	b->nameinfo[b->writepos] = data;
	b->writepos++;
	if (b->writepos >= BUFFER_SIZE)
	b->writepos = 0;
	/* 设置缓冲区非空的条件变量*/
	pthread_cond_signal(&b->notempty);

	pthread_mutex_unlock(&b->lock);
} 
/* 从缓冲区中取出整数*/
struct namemsg get(struct prodcons *b)
{
	struct namemsg data;
	pthread_mutex_lock(&b->lock);

	/* 等待缓冲区非空*/
	if (b->writepos == b->readpos)
	{
		pthread_cond_wait(&b->notempty, &b->lock);
	}
	/* 读数据,移动读指针*/
	data = b->nameinfo[b->readpos];
	b->readpos++;
	if (b->readpos >= BUFFER_SIZE)
	b->readpos = 0;
	/* 设置缓冲区未满的条件变量*/
	pthread_cond_signal(&b->notfull);
	pthread_mutex_unlock(&b->lock);

	return data;
}

/* 测试:生产者线程将1 到10000 的整数送入缓冲区,消费者线
程从缓冲区中获取整数,两者都打印信息*/
#define OVER (-1)
struct prodcons nameinfobuf;

/* 这里会生成两个文件, filename1.log 存放文件夹下的文件名，包括以往的所有文件名
 *					   filename2.log 存放没有转换的文件名，转换后会从文件中清除
 *					   
 * 转换文件线程 */
void *transform_file_pthread (void *p)
{
	struct namemsg nameinfo;
	memset(&nameinfo, 0, sizeof(struct namemsg));
	printf ("转换文件线程开始...\n");
			while(1)
			{
				printf ("放入缓冲池\n");
		strcpy(nameinfo.nfexmsg.srcip,"eee");
		strcpy(nameinfo.nfexmsg.desip,"ddd");
		strcpy(nameinfo.nfexmsg.filename,"ccc");
		strcpy(nameinfo.transformname,"bbb");
		strcpy(nameinfo.fileformat,"aaa");

				put(&nameinfobuf, nameinfo);
			}
	printf ("转换文件线程结束...\n");
	pthread_exit((void*)1);
}

/* 匹配文件线程 */
void *match_file_pthread (void *p)
{
	struct namemsg nameinfo;
	memset(&nameinfo, 0, sizeof(struct namemsg));
	printf ("匹配文件线程开始...\n");

			while(1)
			{
				printf("从缓冲池中取得消息......\n");
				nameinfo = get(&nameinfobuf);	
				printf("从缓冲池中取得消息......\n");
#if 1
		printf("2-nfexmg.srcip=%s\n", nameinfo.nfexmsg.srcip);
		printf("2-nfexmg.desip=%s\n", nameinfo.nfexmsg.desip);
		printf("2-nfexmg.filename=%s\n", nameinfo.nfexmsg.filename);
		printf("2-namemsg.transformname=%s\n", nameinfo.transformname);
		printf("2-namemsg.fileformat=%s\n", nameinfo.fileformat);
#endif
			}
	printf ("匹配文件线程结束...\n");
	pthread_exit((void*)1);
}


int main ()
{
	printf ("客户端启动...\n");
	/* 注册自定义信号函数 */
	//signal (SIGINT, fa);

	init(&nameinfobuf);
	/* 创建接收https线程，发送到https线程,发送到sftp线程,匹配文件线程 */
	pthread_t id1, id2, id3, id4, id5, id6, id7, id8;

	/* 创建转换文件线程 */
	pthread_create (&id1, 0, transform_file_pthread, 0);

	/* 创建匹配文件线程 */
	pthread_create (&id2, 0, match_file_pthread, 0);

	/* 创建计算机状态线程 */
	//pthread_create (&id3, 0, computerstate_pthread, 0);

	pthread_join (id1, 0);
	pthread_join (id2, 0);
	//pthread_join (id3, 0);

	DEBUG ("客户端关闭...\n");
	return 0;
}
