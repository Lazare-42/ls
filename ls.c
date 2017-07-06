#include "ls.h"
#include "libft.h"

void	ls(char *name, int options)
{
	t_ls *stock = NULL;
	stock = ft_store(name);
	(options & CMD_a) ? stock = ft_advance_stock_if_no_a(stock) : stock;
	(options & CMD_r) ? ft_ls_reverse(&(stock)) : stock;
	(options & CMD_l) ? ft_CMD_r(stock) : ft_print_normal(stock);  
}
