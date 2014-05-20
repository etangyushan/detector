/*
 Author: wangyao
 Email: wangyao@cs.hit.edu.cn
 */
#include "acsmx.h"

/*
 *  Text Data Buffer
 */
unsigned char text[MAXLEN];
extern int nline;



ACSM_STRUCT* acsmMatching(char *filePath, char **argv, int count,int maxLegth) {

	int i, nocase = 0;
	FILE *fd;
	ACSM_STRUCT * acsm;

	if (filePath == NULL) {
		fprintf(stderr, "no fileURL");
		exit(0);
	}

	acsm = acsmNew();

	fd = fopen(filePath, "r");
	if (fd == NULL) {
		fprintf(stderr, "Open file error!\n");
		exit(1);
	}
	for (i = 0; i < count; i++) {

		acsmAddPattern(acsm, (unsigned char*)argv[i], strlen(argv[i]), nocase);
	}

	/* Generate GtoTo Table and Fail Table */
	acsmCompile(acsm);

	/*Search Pattern*/
	while (fgets((char *)text, maxLegth, fd)) {
		acsmSearch(acsm, text, strlen((char*)text), PrintMatch);
		nline++;
	}

	fclose(fd);
	fd = NULL;
	return acsm;
}

int main(int argc, char **argv) {
	char *name[5] = { "中国石油", "GNU", "Crystal", "Stef", "Sammy" };
	ACSM_STRUCT * acsm;
	int i = 0;
	//while(i<5)
	{
//	acsm = acsmMatching("/root/detector/after_transform/aaa.txt", name, 5,16384);
	acsm = acsmMatching("gpl.txt", name, 5,16384);
	PrintSummary(acsm->acsmPatterns);
	printf("ok\n");
	i++;
	}
	acsmFree(acsm);
	return 0;
}
