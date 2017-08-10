//ligne 52 cas gu getgrgid nuul a gerer

#include "ls.h"
#include <sys/xattr.h> // for extended file attributes impression (@)
#include <pwd.h> // for getpwuid
#include <grp.h> // for getgrgido
#include <time.h> //self_explanatory

char   ft_mode(int mode)
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
		(c = '?');
	return (c);
}

void	ft_print_rights(t_ls *stock, char *path)
{
	int attributes;
	acl_t acl;
	char c;
	int mode;

	mode = stock->stat.st_mode;
	attributes = listxattr(path, NULL, stock->stat.st_size, XATTR_NOFOLLOW);
	acl = acl_get_file(path, ACL_TYPE_EXTENDED);
	c = ft_mode(mode);
	ft_putchar (c);
	ft_putchar( (stock->stat.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar( (stock->stat.st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar( (stock->stat.st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar( (stock->stat.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar( (stock->stat.st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar( (stock->stat.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar( (stock->stat.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar( (stock->stat.st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar( (stock->stat.st_mode & S_IXOTH) ? 'x' : '-');
	(attributes) ? ft_putchar('@') : (acl) ? ft_putchar('+') : ft_putchar(' ');
	(acl) ? acl_free((void*)acl) : 0;
}

void    ft_print_GRP_USR(t_ls *stock, int *max_size)
{
	struct group *grp;

	ft_put_whites(max_size[0], stock->stat.st_nlink, 1);
	ft_putnbr(stock->stat.st_nlink);
	ft_putchar(' ');
	ft_putstr(getpwuid(stock->stat.st_uid)->pw_name);
	ft_put_whites(max_size[1], 
			ft_strlen(getpwuid(stock->stat.st_uid)->pw_name), 2);
	grp = getgrgid(stock->stat.st_gid);
	if (grp)
	{
		ft_putstr(grp->gr_name);
		ft_put_whites(max_size[2], ft_strlen(grp->gr_name), 3);
		return;
	}
	ft_putstr(strerror(errno));
	ft_put_whites(max_size[2], ft_strlen(strerror(errno)), 3);
}

void		print_lnkabout(char *fpath)
{
	int		path_size;
	char	buf[1024];

	path_size = readlink(fpath, buf, 1024);
	buf[path_size] = '\0';
	ft_putstr(" -> ");
	ft_putstr(buf);
}

int		ft_CMD_l(t_ls *tmp, char *foldername, int file_mode)
{
	int  *max_size;
	time_t local_time;
	char *path;
	t_ls *stock;

	stock = tmp;
	max_size = ft_max_size(stock, file_mode);
	local_time = time(&local_time);
	if (!stock)
			ft_putchar('\n');
	while (stock)
	{
		path = find_path(stock->name, foldername);
		ft_print_rights(stock, path);
		ft_print_GRP_USR(stock, max_size);
		ft_put_whites(max_size[3], stock->stat.st_size, 4);
		ft_putnbr((int)stock->stat.st_size);
		ft_putchar(' ');
		ft_print_time(stock, local_time);
		ft_putchar(' ');
		ft_print_name(stock->name, stock->stat.st_mode);
		if (S_ISLNK(stock->stat.st_mode))
			print_lnkabout(path);
		if (stock->next)
			ft_putchar('\n');
		stock = stock->next;
		ft_memdel((void**)&path);
	}
	ft_memdel((void**)&max_size);
	return(1);
}
