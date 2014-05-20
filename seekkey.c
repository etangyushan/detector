#include "./seekkey.h"

extern int nline;
#define MAXBUF 128

/* 判断是否匹配 ,匹配的关键字标志位为 "match"*/
struct policymsg
acsm_match_policy (ACSM_PATTERN * pattern, struct policymsg pinfo)
{

	struct policymsg policyinfo = pinfo;
	int i = policyinfo.size - 1;
	for (; pattern != NULL; pattern = pattern->next) {
		if (pattern->nocase) {
			printf ("%12s : %5d\n", pattern->patrn, pattern->nmatch);

		}
		else {
			printf ("----%12s : %5d----\n", pattern->casepatrn, pattern->nmatch);
			printf ("patrn = %s, keyword = %s\n", pattern->patrn, policyinfo.keyword[i]);
			if (   //(strcmp(toupper(pattern->patrn), policyinfo.keyword[i]) == 0) &&
				   pattern->nmatch == atoi (policyinfo.keycount[i])) {
				/* 匹配策略就把标志位设置为 "match" */
				strcpy (policyinfo.flag[i], "match");
			}
#if 1
			struct Coordinate *coo = pattern->coordinate;
			for (; coo != NULL; coo = coo->next) {
				printf ("行：%d 列：%d\n", coo->line, coo->colm);
			}
#endif
		}
		i--;
	}
	return policyinfo;
}

/* 产生匹配信息 */
ACSM_STRUCT *
acsmMatching (char *filePath, char argv[][LENMAX], int count, int maxLegth)
{
	char text[MAXLEN];

	int i, nocase = 0;
	FILE *fd;
	ACSM_STRUCT *acsm;

	if (filePath == NULL) {
		fprintf (stderr, "no fileURL");
		exit (0);
	}

	acsm = acsmNew ();

	fd = fopen (filePath, "r");
	if (fd == NULL) {
		fprintf (stderr, "Open file error!\n");
		exit (1);
	}
	for (i = 0; i < count; i++) {

		acsmAddPattern (acsm, (unsigned char *)argv[i], strlen (argv[i]), nocase);
	}

	/* Generate GtoTo Table and Fail Table */
	acsmCompile (acsm);
	printf ("ok1\n");

	/*Search Pattern */
	while (fgets (text, maxLegth, fd)) {
		acsmSearch (acsm, text, strlen (text), PrintMatch);
		printf ("ok2=filepath=%s\n", filePath);
		nline++;
		printf ("ok3\n");
	}

	fclose (fd);
	fd = NULL;
	return acsm;
}

/* 匹配关键字 */
//int seekkey(struct namemsg *nameinfo, char *keyword[], int len)
struct policymsg
seekkey (struct namemsg *nameinfo, struct policymsg policyinfo)
{
	//char command[1024] = {};
	char filename[256] = { };
	char matchfile[256] = { };
	char logmsg[100] = { };
	char *tmp = "./tmp";
	char *name = (char *)malloc (256);
	memset (name, 0, 256);
	int size = 0;
	ACSM_STRUCT *acsm;
	struct policymsg policy_match;
	//printf ("keyword=%s\n", keyword);
	/* 提取文件名 */
	getname (nameinfo->transformname, &name);

	/* 生成的匹配信息文件 */
	//sprintf (matchfile, "%s/%s.match", MATCHDIR, name);
	//sprintf (nameinfo->snapshot, "%s/%s.match", MATCHDIR, name);

	/* 需要匹配的文件名,绝对路径 */
	sprintf (filename, "%s/%s.txt", AFTRANSFORM, name);
	//strcpy(filename, "./gpl.txt");
	printf ("seekkey.c-111-filename=%s\n", filename);

	size = policyinfo.size;
	printf ("size=%d\n", size);
	/* 使用acsm多模式匹配, 得到匹配信息 */
	printf ("获得匹配信息......\n");
	acsm = acsmMatching (filename, policyinfo.keyword, size, MAXBUF);

	/* 将匹配信息与策略比较确定是否匹配 */
	printf ("匹配结果和策略比较......\n");
	policy_match = acsm_match_policy (acsm->acsmPatterns, policyinfo);

	/* 打印匹配结果 */
	//PrintSummary(acsm->acsmPatterns);

	/* 释放空间 */
	acsmFree (acsm);

#if 0
	//char *key[5] = { "中国石油", "GNU", "Crystal", "Stef", "Sammy" };
	//acsm = acsmMatching(filename, key, 5,16384);
	//ACSM_STRUCT * acsm = acsmMatching("/root/detector/after_transform/aaa.txt", key, 5,16384);
	//ACSM_STRUCT *acsm = acsmMatching("aaa.txt", key, 5,16384);
	//sprintf (command, "grep -Hni %s %s >> %s", keyword, nameinfo->transformname, tmp);
	//printf ("ok2\n");
	//printf ("transformname=%s\n", nameinfo->transformname);
	sprintf (command, "cp %s ./ -rf", nameinfo->transformname);
	system (command);
	//printf ("command:%s\n", command);
	sprintf (command, "./acsmx  %s.txt %s > %s", name, keyword, tmp);
	printf ("command:%s\n", command);
	system (command);
	size = get_file_size (tmp);
	//printf ("tmp=%s\n", tmp);
#endif

#if 0
	size = 0;
	if (0 == size) {
		/* 丢掉并记录日志 */
		//printf ("丢掉并记录日志......\n");
#if 0
		/* 删除a.txt ,没有删除.doc */
		remove (filename);
		remove (name);
#endif
		/* 写入日志信息有 文件名，关键字 */
		sprintf (command, "rm  %s.txt -rf", name);
		system (command);
		memset (logmsg, 0, sizeof (logmsg));
		sprintf (logmsg, "关键字:\"%s\"  不匹配文件:\"%s\"\n", keyword, nameinfo->filename);
		//my_syslog (NOMATCHLOG, filename, logmsg);
		return -1;
	}
	else if (size > 0) {
		//sprintf (command, "grep -Hni %s %s >> %s", keyword, nameinfo->transformname, matchfile);
		//sprintf (command, "./acsmx  %s %s >> %s",  nameinfo->transformname, keyword, matchfile);
		sprintf (command, "./acsmx  %s.txt %s >> %s", name, keyword, matchfile);
		//printf("command=%s\n", command);
		system (command);
		sprintf (command, "rm  %s.txt -rf", name);
		system (command);

		printf ("匹配成功并保存......\n");
		/* 写入日志信息有 文件名关键字 */
		sprintf (command, "echo %s >> %s", keyword, matchfile);
		system (command);
		memset (logmsg, 0, sizeof (logmsg));
		sprintf (logmsg, "关键字:\"%s\" 匹配文件:\"%s\"成功\n", keyword, nameinfo->filename);
		//my_syslog(MATCHLOG, filename, logmsg);
	}

	sprintf (command, "rm %s -f", tmp);
	system (command);
#endif
	free (name);
	name = NULL;
	return policy_match;
}

/* 对文件记录的.txt文件进行匹配 */
int
matchfile (struct namemsg nameinfo, char *policyfile)
{
#if 0
	printf ("3-nfexmg.srcip=%s\n", nameinfo.nfexmsg.srcip);
	printf ("3-nfexmg.desip=%s\n", nameinfo.nfexmsg.desip);
	printf ("3-nfexmg.filename=%s\n", nameinfo.nfexmsg.filename);
	printf ("3-namemsg.transformname=%s\n", nameinfo.transformname);
	printf ("3-namemsg.fileformat=%s\n", nameinfo.fileformat);
#endif
	int res = 0;
	int flag = 0;
	int i = 0;
	struct event ev;
	struct policymsg policyinfo;
	struct policymsg policy_match;

	printf ("获取策略文件的匹配信息: %s\n", policyfile);

	policyinfo = get_policy_json (policyfile);

	//char *policyfile[5] = { "中国石油", "GNU", "Crystal", "Stef", "Sammy" };

	/* 匹配关键字 */
	printf ("217-调用比较函数......\n");
	policy_match = seekkey (&nameinfo, policyinfo);

	flag = 0;
	while (i < policy_match.size) {
		printf ("flag=%s\n", policy_match.flag[i]);
		if (strcmp (policy_match.flag[i], "match") == 0) {
			printf ("文件匹配......\n");
			flag++;
		}
		else {
			printf ("文件不匹配......\n");
		}

		i++;
	}
	if (flag) {
		/* 匹配后产生事件 */
		printf ("匹配成功...发送匹配信息......\n");
		ev.nameinfo = nameinfo;
		logevent (ev);
	}
	return 0;
}

#if 0
/* 对文件记录的.txt文件进行匹配 */
int
matchfile (struct namemsg nameinfo, char *policyfile)
{
#if 0
	printf ("3-nfexmg.srcip=%s\n", nameinfo.nfexmsg.srcip);
	printf ("3-nfexmg.desip=%s\n", nameinfo.nfexmsg.desip);
	printf ("3-nfexmg.filename=%s\n", nameinfo.nfexmsg.filename);
	printf ("3-namemsg.transformname=%s\n", nameinfo.transformname);
	printf ("3-namemsg.fileformat=%s\n", nameinfo.fileformat);
#endif
	char savefilename[256][256] = { };
	char keyword[256] = { };
	char *suffix;
	FILE *pf;
	int res = 0;
	int flag = 0;
	size_t read;
	struct policykey namekey;
	struct event ev;
	//struct namemsg nameinfo = info;

	//printf("seekkey.c-75-transformname=%s\n", nameinfo.transformname);
	memset (savefilename, 0, sizeof (savefilename));

	pf = fopen (policyfile, "r");
	if (pf == NULL) {
		perror ("seekkey.c-82-fopen");
		return -1;
	}
	/* 获取关键字 */
	flag = 0;
	//while ((read = fread (&namekey, sizeof(namekey), 1, pf)) > 0) 
	{
		printf ("读取策略关键字文件......\n");
#if 1
		/* 匹配关键字 */
		printf ("调用比较函数......\n");
		///////////////////////////////////////////////
		/* 来自java的关键字 */
		strcpy (namekey.keyword, policyfile);
		//////////////////////////////////////////////
		res = seekkey (&nameinfo, namekey.keyword);
		//printf("seekkey.c-99-transformname=%s\n", nameinfo.transformname);
		if (res == 0) {
			printf ("文件匹配......\n");
			flag++;
		}
		else {
			printf ("文件不匹配......\n");
		}
#endif
	}
	//printf("seekkey.c-104\n");
	if (flag) {
		/* 匹配后产生事件 */
		printf ("文件匹配...发送给消息队列\n");
		//      printf(".................seekkey.c.......................\n");
		/* memset(&ev, 0, sizeof(ev)); */
		ev.nameinfo = nameinfo;
		logevent (ev);
	}

	fclose (pf);
	pf = NULL;

	return 0;
}
#endif

#if 0
int
main ()
{
	int res;
#if 0
	char my_path[1024] = { };
	/* int res = seekkey ("a.txt", "tang"); */
	char *fpath;
	fpath = (char *)malloc (256);
	getcwd (fpath, 256);
	//printf("路径%s",fpath);
	char *dirname = "file";
	char *keywordfile = "keyword.log";
	sprintf (my_path, "%s/%s", fpath, dirname);
	//int res = matchfile (dirname, keywordfile);
#endif
	struct namemsg nameinfo;
	memset (&nameinfo, 0, sizeof (struct namemsg));
	int i = 2;
	//while(i--)
	//while(1)
	{
		//int res = seekkey (nameinfo.transformname, namekey.keyword);
		//char *my_path = "/root/detector/after_transform/atfilename.log";
		//char *keywordfile = "/root/detector/policy/keyword.plc";
		//char *keywordfile = "a";
		//int res = matchfile (my_path, keywordfile);

		char *fullname = "gpl.txt";
		char *policyfile = "tmp.json";
		strcpy (nameinfo.transformname, fullname);
		while (1)
			res = matchfile (nameinfo, policyfile);
		//char *keyword = "tang";
		//res = seekkey(fullname, keyword);
		printf ("main\n");
	}
}
#endif
