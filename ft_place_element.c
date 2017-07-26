#include "ls.h"
#include "libft.h"

t_ls *ft_place_elem_according_to_time(t_ls *stock, t_ls *new)
{
	t_ls *check;
	int t1;
	int t2;

	check = stock;
	t1 = check->stat.st_mtimespec.tv_sec;
	t2 = new->stat.st_mtimespec.tv_sec;
	if (t2 >= t1)
	{
		new->next = stock;
		return (stock = new);
	}
	while(check->next &&  t2 <= (t1 = check->next->stat.st_mtimespec.tv_sec))
		check = check->next;
	new->next = check->next;
	check->next = new;
	return (stock);
}

t_ls *ft_place_elem(t_ls *stock, t_ls *new, int options)
{
	t_ls	*check;

	check = stock;
	if (!(options & CMD_a) && new->name[0] == '.')
	{
		ft_memdel((void**)&new);
		return (stock);
	}
	if (!(stock))
		return (stock = new);
	if (options & CMD_t)
		return (ft_place_elem_according_to_time(stock, new));
	if (ft_strcmp(check->name, new->name) > 0)
	{
		new->next = stock;
		return (stock = new);
	}
	while (check->next && ft_strcmp(check->next->name, new->name) < 0)
		check = check->next;
	new->next = check->next;
	check->next = new;
	return (stock);
}
