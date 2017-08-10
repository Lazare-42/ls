#include "ls.h"

void	ft_free(t_ls **stock)
{
	t_ls *tmp;
	while (*stock)
	{
		tmp = (*stock)->next;
		free((*stock)->name);
		ft_memdel((void**)stock);
		*stock = tmp;
	}
}

void	ft_CMD_r(t_ls **begin_list)
{
	t_ls*list;
	t_ls*q;
	t_ls*p;

	list = *begin_list;
	p = NULL;
	q = NULL;
	while (list)
	{
		p = list;
		list = list->next;
		p->next = q;
		q = p;
	}
	*begin_list = p;
}
