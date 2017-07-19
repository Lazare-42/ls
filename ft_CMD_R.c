#include "ls.h"
#include "libft.h"

void	ft_CMD_R(t_ls *stock,char *name, int options)
{
	t_ls *tmp;
	char *new_name;

	tmp = stock;
	while (stock)
	{
		if (S_ISDIR(stock->stat.st_mode) && stock->name[0] != '.')
		{
			ft_putchar('\n');
			ft_putchar('\n');
			ft_putstr(stock->name);
			ft_putstr(":\n");
			name = ft_strjoin(name, "/");
			new_name = ft_strjoin(name, stock->name);
			ls(new_name, options);
		}
		stock = stock->next;
	}
}
