#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

int main()
{
	system ("sed -i 'aaa -h -n'");
}
