#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mydir.h"
struct policykey
{
	char keyword[256];
};

int
showstrkeyword (char *keyfile)
{
	struct policykey key;
	memset (&key, 0, sizeof (struct policykey));
	FILE *pf = fopen (keyfile, "r");
	while (fread (&key, sizeof (struct policykey), 1, pf)) {
		printf ("keyword=%s\n", key.keyword);
	}
	fclose (pf);
	pf = NULL;
}

int
overkeyword (char *srckeyword, char *deskeyword)
{
	struct policykey key;
	memset (&key, 0, sizeof (struct policykey));
	FILE *repf;
	FILE *wrpf;
	repf = fopen (srckeyword, "r");
	if (repf == NULL) {
		perror ("fopen");
	}
	//wrpf = fopen(deskeyword, "a");
	wrpf = fopen (deskeyword, "w");
	if (wrpf == NULL) {
		perror ("fopen");
	}

	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int size = 0;

	while ((read = getline (&line, &len, repf)) != -1) {
		size = strlen (line);
		line[size - 1] = '\0';
		//printf("%s\n", line);
		strcpy (key.keyword, line);
		fwrite (&key, sizeof (struct policykey), 1, wrpf);
	}
	if (line) {
		free (line);
	}

	fclose (repf);
	repf = NULL;
	fclose (wrpf);
	wrpf = NULL;
}

int
main ()
{
	char *src = KEYWORD;
	char des[256] = { };
	strcpy (des, KEYWORD);
	strcat (des, "key");
	overkeyword (src, des);
	showstrkeyword (des);
}
