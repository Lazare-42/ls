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
		ft_putstr(tmp->name);
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
