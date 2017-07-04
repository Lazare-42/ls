#include "ls.h"
#include "libft.h"

void	ls(char *name, int options)
{
	options++;
	t_ls *stock = NULL;
	stock = ft_store(name);
	(options & CMD_l) ? ft_print_normal(stock) : ft_CMD_r(stock);  
}
