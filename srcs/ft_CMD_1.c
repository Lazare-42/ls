#include "ls.h"

void ft_CMD_1(t_ls *stock)
{
	t_ls *tmp;

	tmp = stock;
	while (tmp)
	{
		ft_print_name(tmp->name, tmp->stat.st_mode);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}
