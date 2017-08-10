#include "ls.h"
#include <time.h>
#include <sys/xattr.h> // for extended file attributes impression (@)
#include <pwd.h> // for getpwuid
#include <grp.h> // for getgrgido
#include <time.h> //self_explanatory

void	ft_print_time(t_ls *stock, time_t local_time)
{
	char *tmp;
	char *file_time;

	file_time = ctime(&(stock->stat.st_mtime));
	tmp = NULL;
	if (((int)local_time - (int)stock->stat.st_mtime) > 15778800)
	{
		tmp = ft_strsub(file_time, 4, 7);
		ft_putstr(tmp);
		ft_strdel(&tmp);
		tmp = ft_strsub(&file_time[19], 0, 5);
		ft_putstr(tmp);
		ft_strdel(&tmp);
		return ;
	}
	tmp = ft_strsub(file_time, 4, 12);
	ft_putstr(tmp);
	ft_strdel(&tmp);
}

void	ft_print_name(char *name, int st_mode)
{
	if (S_ISDIR(st_mode))
	{
		ft_putstr("\e[0;96m");
		ft_putstr(name);
		ft_putstr("\e[0m");
	}
	else if (S_ISLNK(st_mode))
	{
		ft_putstr("\033[0;35m");
		ft_putstr(name);
		ft_putstr("\e[0m");
	}
	else if (st_mode & S_IXUSR)
	{
		ft_putstr("\033[0;31m");
		ft_putstr(name);
		ft_putstr("\e[0m");
	}
	else
		ft_putstr(name);
}

void	ft_print_rights(t_ls *stock, char *path)
{
	int attributes;
	acl_t acl;
	char c;
	int mode;

	mode = stock->stat.st_mode;
	attributes = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
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
