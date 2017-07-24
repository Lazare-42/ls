#include "ls.h"
#include "libft.h"
#include <sys/xattr.h> // for extended file attributes impression (@)

void	filetypeletter(int mode)
{
	char c;

	if (S_ISREG(mode))
		c = '-';
	else if (S_ISDIR(mode))
		c = 'd';
	else if (S_ISBLK(mode))
		c = 'b';
	else if (S_ISCHR(mode))
		c = 'c';
	else if (S_ISFIFO(mode))
		c = 'p';
	else if (S_ISLNK(mode))
		c = 'l';
	else if (S_ISSOCK(mode))
		c = 's';
	else
	{
		c = '?';
	}
	ft_putchar (c);
}

void	ft_print_rights(t_ls *stock, char *path)
{
	int attributes;
	acl_t acl;

	path = NULL;
	attributes = listxattr(path, NULL, stock->stat.st_size, XATTR_NOFOLLOW);
	acl = acl_get_file(path, ACL_TYPE_EXTENDED);
	filetypeletter(stock->stat.st_mode);
	ft_putchar( (stock->stat.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar( (stock->stat.st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar( (stock->stat.st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar( (stock->stat.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar( (stock->stat.st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar( (stock->stat.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar( (stock->stat.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar( (stock->stat.st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar( (stock->stat.st_mode & S_IXOTH) ? 'x' : '-');
	//(attributes) ? ft_putchar('@') : (acl) ? ft_putchar('+') : ft_putchar(' ');
	if (acl)
		acl_free((void*)acl);
}

int		ft_CMD_l(t_ls *stock, char *foldername)
{

	int  *max_size;
	char *path;

	max_size = ft_max_size(stock);
	while (stock)
	{
		path = find_path(stock->name, foldername);
		ft_print_rights(stock, path);
		ft_putchar('\n');
		stock = stock->next;
	}
	return(1);
}
