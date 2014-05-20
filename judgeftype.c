#include "./judgeftype.h"

#define ATPATH "/root/detector/after_transform"
#define BFPATH "/root/detector/before_transform"
//#define ATPATH "./testdoc"
#if 0
int
filetotxt2 (struct namemsg **name)
{
	char command[1024] = { };
	char *fname = (char *)malloc (256);
	memset (fname, 0, 256);
	char comtype[16] = { };
	int flag = 0;
	ssize_t read;
	struct namemsg *nameinfo = *name;

	/* 读取记录文件 */
	/* 判断文件类型  */
	flag = file_type (nameinfo->filename);
	//printf ("ok\n");

	/* 从文件全名中去掉后缀提取名字 */

	//printf("filename=%s\n",nameinfo->filename);
	//split_name(nameinfo->filename, &fname);
	//memset (fname, 0, sizeof(fname));
	getname (nameinfo->filename, &fname);
	//printf("filename=%s\n",nameinfo->filename);
	printf ("抓到文件:%s\n", nameinfo->filename);
	//split_name(nameinfo->filename, &fname);
	//printf("fname=%s\n",fname);
	//printf ("ok2\n");

	memset (command, 0, sizeof (command));

	/* 文件类型flag= 1:.doc, 2:.pdf, 3:.ppt */
	switch (flag) {
	case 1:
		strcpy (comtype, "catdoc");
		sprintf (command, "%s %s > %s/%s.txt", comtype, nameinfo->filename, ATPATH, fname);
		//printf ("command-doc=%s\n", command);
		int ret = system (command);
		//printf("ret =%d\n", ret);

		//printf ("command2=%s\n", command);

		/* 产生一个转换后的文件名绝对路径的文件 */
		//printf("nameinfo->transformname=%s\n", fname);
		sprintf (nameinfo->transformname, "%s/%s.txt", ATPATH, fname);
		strcpy (nameinfo->fileformat, "doc");
		/* 将转换后的文件名写入记录 */
		printf ("这个文件是\".doc\"类型: %s\n", command);
		break;

	case 2:
		strcpy (comtype, "pdftotext");
		sprintf (command, "%s %s %s/%s.txt", comtype, nameinfo->filename, ATPATH, fname);
		system (command);
		//printf ("command-pdf=%s\n", command);

		/* 产生一个转换后的文件名的文件 */
		sprintf (nameinfo->transformname, "%s/%s.txt", ATPATH, fname);
		strcpy (nameinfo->fileformat, "pdf");
		printf ("这个文件是\".pdf\"类型: %s\n", command);
		break;
	}

	free (fname);
	fname = NULL;

	return 0;
}
#endif

int
filetotxt (struct namemsg *name)
{
	char command[1024] = { };
	char *fname = (char *)malloc (256);
	memset (fname, 0, 256);
	char comtype[16] = { };
	int flag = 0;
	ssize_t read;
	struct namemsg *nameinfo = name;

	/* 读取记录文件 */
	/* 判断文件类型  */
	flag = file_type (nameinfo->filename);
	//printf ("ok\n");

	/* 从文件全名中去掉后缀提取名字 */

	//printf("filename=%s\n",nameinfo->filename);
	//split_name(nameinfo->filename, &fname);
	//memset (fname, 0, sizeof(fname));
	printf ("抓到的文件名称是:\"%s\"\n", nameinfo->filename);
	getname (nameinfo->filename, &fname);
	//printf("filename=%s\n",nameinfo->filename);
	//split_name(nameinfo->filename, &fname);
	//printf("fname=%s\n",fname);
	//printf ("ok2\n");

	memset (command, 0, sizeof (command));

	/* 文件类型flag= 1:.doc, 2:.pdf, 3:.ppt */
	switch (flag) {
	case 1:
		strcpy (comtype, "catdoc");
		sprintf (command, "%s %s > %s/%s.txt", comtype, nameinfo->filename, ATPATH, fname);
		//printf ("command-doc=%s\n", command);
		int ret = system (command);
		//printf("ret =%d\n", ret);

		//printf ("command2=%s\n", command);

		/* 产生一个转换后的文件名绝对路径的文件 */
		//printf("nameinfo->transformname=%s\n", fname);
		sprintf (nameinfo->transformname, "%s/%s.txt", ATPATH, fname);
		strcpy (nameinfo->fileformat, "doc");
		/* 将转换后的文件名写入记录 */
		//printf("抓到文件是\".doc\"类型: %s\n", command);
		printf ("抓到的文件类型是:\".doc\"\n");
		break;

	case 2:
		strcpy (comtype, "pdftotext");
		sprintf (command, "%s %s %s/%s.txt", comtype, nameinfo->filename, ATPATH, fname);
		system (command);
		//printf ("command-pdf=%s\n", command);

		/* 产生一个转换后的文件名的文件 */
		sprintf (nameinfo->transformname, "%s/%s.txt", ATPATH, fname);
		strcpy (nameinfo->fileformat, "pdf");
		//printf("这个是.pdf: %s\n", command);
		printf ("抓到文件类型是\".pdf\"\n");
		break;
	}

	free (fname);
	fname = NULL;

	return 0;
}

/* 根据后缀判断文件类型 1:.doc, 2:.pdf, 3:.ppt*/
int
file_type (char *fname)
{
	char *suffix = (char *)malloc (32);
	memset (suffix, 0, 32);
	split_suffix (fname, &suffix);
	//printf ("file_type-140\n");
	//printf ("suffix=%d\n", strlen(suffix));
	int flag;
	if (0 == strcmp (suffix, ".doc")) {
		flag = 1;
	}
	else if (0 == strcmp (suffix, ".pdf")) {
		flag = 2;
	}
	else if (0 == strcmp (suffix, ".ppt")) {
		flag = 3;
	}
	else {
		flag = 0;
	}
	free (suffix);
	suffix = NULL;
	//printf ("flag=======%d\n", flag);
	return flag;
}

#if 0
int
main ()
{
	//filetotxt(DIRNAME);
	//char *filename = "testdoc/name.log";
	int i = 10;
	struct namemsg nameinfo;
	//while(i--)
	while (1) {
		strcpy (nameinfo.filename, "aaa.doc");

		filetotxt (&nameinfo);
	}
	//printf ("filename=%s\n", filename);
	//unsigned long aa = get_file_size (filename);
	//printf ("aa=%ld\n", aa);
}
#endif
