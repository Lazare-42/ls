#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
int  main()
{
	DIR *dir;
	struct dirent *dent;
	dir = opendir(".");
	struct stat sb;

	if(dir != NULL)
	{
		while((dent=readdir(dir))!=NULL)
		{
			if((strcmp(dent->d_name,".")==0 || strcmp(dent->d_name,"..")==0 || (*dent->d_name) == '.' ))
			{
			}
			else
				printf("%s\n", dent->d_name);
			if (!(stat(dent->d_name, &sb)))
				printf("%llu\n", sb.st_size);
		}
	}
		if (closedir(dir))
			return (-1);
	return (0);
}
