#include "ls.h"

void	ft_CMD_R(t_ls *stock,char *name, int options)
{
	t_ls *tmp;
	char *new_name;
	int i;

	i = 1;
	tmp = stock;
	while (stock)
	{
		if (i)
			ft_putchar('\n');
		new_name = NULL;
		if (S_ISDIR(stock->stat.st_mode) && ft_strcmp("..", stock->name) 
				&& ft_strcmp(".", stock->name))
		{
			new_name = ft_strjoin(ft_strjoin(name, "/"), stock->name);
			ft_putchar('\n');
			ft_putstr(new_name);
			ft_putstr(":");
			ls(new_name, options, 1, 0);
		}
		if (new_name)
			ft_bzero(new_name, ft_strlen(new_name));
		stock = stock->next;
		new_name = NULL;
		i = 0;
	}
}
