//ligne 52 cas gu getgrgid nuul a gerer

#include "ls.h"
#include <sys/xattr.h> // for extended file attributes impression (@)
#include <pwd.h> // for getpwuid
#include <grp.h> // for getgrgido
#include <time.h> //self_explanatory

static void    ft_print_GRP(t_ls *stock, int *max_size)
{
	struct group *grp;

	ft_put_whites(max_size[0], stock->stat.st_nlink, 1);
	ft_putnbr(stock->stat.st_nlink);
	ft_putchar(' ');
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


int		ft_CMD_g(t_ls *tmp, char *foldername, int file_mode)
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
		ft_print_GRP(stock, max_size);
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
