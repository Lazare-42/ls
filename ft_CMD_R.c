#include "ls.h"
#include "libft.h"

void	ft_CMD_R(t_ls *stock,char *name, int options)
{
	t_ls *tmp;
	char *new_name;

	tmp = stock;
	while (stock)
	{
		new_name = NULL;
		if (S_ISDIR(stock->stat.st_mode) && ft_strcmp("..", stock->name) && ft_strcmp(".", stock->name))
		{
			new_name = ft_strjoin(ft_strjoin(name, "/"), stock->name);
			ft_putstr(new_name);
			ft_putstr(":\n");
			ls(new_name, options);
		}
		if (new_name)
			ft_bzero(new_name, ft_strlen(new_name));
		stock = stock->next;
		new_name = NULL;
	}
}
