#include "ls.h"

char	*find_path(char *name, char *foldername)
{
	char *path;

	path = ft_strjoin(foldername, "/");
	path = ft_strjoinfree(&path, &name, 'L');
	return (path);
}
