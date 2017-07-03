#include "ls.h"

void	ls(char *name, int options)
{
	options++;
	t_ls *stock = NULL;
	stock = ft_store(name);
	ft_print_normal(stock);
	//ft_list_subfolders(name, stock, options);
}
