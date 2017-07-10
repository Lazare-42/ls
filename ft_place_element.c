#include "ls.h"
#include "libft.h"

t_ls *ft_place_elem(char *pathname, t_ls *stock, t_ls *new)
{
	t_ls	*check;

	check = stock;
	if (ft_strcmp(check->name, new->name) > 0)
	{
		new->next = stock;
		return (stock = new);
	}
	while (check->next && ft_strcmp(check->next->name, new->name) < 0)
			check = check->next;
	new->next = check->next;
	check->next = new;
	stat(pathname, &(new->stat));
	return (stock);
}
	

