#include <sys/xattr.h>
#include "ls.h"
#include "libft.h"
#include <pwd.h>
#include <time.h>
#include <grp.h>

void	ft_put_whites(int max_str_len,int  fillup, int options)
{
	if (options == 1 || options == 4)
		fillup = ft_strlen(ft_itoa(fillup));
	while (fillup <= max_str_len)
	{
		ft_putchar(' ');
		fillup++;
	}
	ft_putchar(' ');
}

int		ft_max_size_2(t_ls *stock, int options)
{
	int max;
	int tmp_val;
	t_ls *tmp;

	max = 0;
	tmp = stock;
	while (tmp && options == 1)
	{
		(tmp->stat.st_nlink > max) ? max = tmp->stat.st_nlink : max;
		tmp = tmp->next;
	}
	while (tmp && options == 2)
	{
		tmp_val = ft_strlen(getpwuid(tmp->stat.st_uid)->pw_name);
		(tmp_val > max) ? max = tmp_val: max;
		tmp = tmp->next;
	}
	return (max);
}
int		ft_max_size(t_ls *stock, int options)
{
	int max;
	struct group *grp;
	t_ls *tmp;

	max = 0;
	tmp = stock;
	if (options == 1 || options == 2)
		max = ft_max_size_2(stock, options);
	while (tmp && options == 3)
	{
		grp = getgrgid(tmp->stat.st_gid);
		((int)ft_strlen(grp->gr_name) > max) ? max = (int)ft_strlen(grp->gr_name) : max;
		tmp = tmp->next;
	}
	while (tmp && options == 4)
	{
		((int)tmp->stat.st_size > max) ?  max = (int)tmp->stat.st_size : max;
		tmp = tmp->next;
	}
	if (options == 1 || options == 4)
		max = ft_strlen(ft_itoa(max));
	return (max);
}
