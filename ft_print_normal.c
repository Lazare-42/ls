#include "ls.h"
#include "libft.h"

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

void	ft_print_simple(char *name, int st_mode)
{
	if (S_ISDIR(st_mode))
	{
		ft_putstr(" \e[0;96m");
		ft_putstr(name);
		ft_putstr("\e[0m");
	}
	else if (S_ISLNK(st_mode))
	{
		ft_putstr(" \033[0;35m");
		ft_putstr(name);
		ft_putstr("\e[0m");
	}
	else if (st_mode & S_IXUSR)
	{
		ft_putstr(" \033[0;31m");
		ft_putstr(name);
		ft_putstr("\e[0m");
	}
	else
	{
		ft_putstr(" \e[0m");
		ft_putstr(name);
		ft_putstr("\e[0m");
	}
}

void ft_print_normal(t_ls *stock)
{
	t_ls *tmp;
	int i;
	int j;

	j = 0;
	i = ft_longest_name(stock);
	tmp = stock;
	while (tmp)
	{
		if (tmp->name)
			ft_print_simple(tmp->name, tmp->stat.st_mode);

		j = (int)ft_strlen(tmp->name);
		while (j < i)
		{
			ft_putchar(' ');
			j++;
		}
		ft_putchar(' ');
		tmp = tmp->next;
	}
}
