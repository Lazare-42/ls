#include "ls.h"
#include <sys/ioctl.h>

int	ft_longest_name(t_ls *stock)
{
	int i;
	t_ls *tmp;

	i = 0;
	tmp = stock;
	while (tmp)
	{
		i = ((int)ft_strlen(tmp->name) > i) ? (int)ft_strlen(tmp->name) : i;
		tmp = tmp->next;
	}
	return (i);
}
void ft_print_normal(t_ls *stock)
{
	t_ls *tmp;
	struct winsize max;
	int i;
	int maxx;
	int j;

	j = 0;
	maxx = 0;
	i = ft_longest_name(stock);
	tmp = stock;
	ioctl(1, TIOCGWINSZ, &max);
	while (tmp)
	{
		j = (int)ft_strlen(tmp->name);
		maxx += j;
		(maxx >= max.ws_col) ? ft_putchar('\n'),maxx = j : 0;
		ft_print_name(tmp->name, tmp->stat.st_mode);
		while (j++ <= i && ++maxx < max.ws_col && tmp->next)
			ft_putchar(' ');
		if (!(tmp->next))
			ft_putchar('\n');
		tmp = tmp->next;
	}
}
