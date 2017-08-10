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
