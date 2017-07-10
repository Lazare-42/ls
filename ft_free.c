#include "ls.h"

void	ft_free(t_ls **stock)
{
	t_ls *tmp;
	while (*stock)
	{
		tmp = (*stock)->next;
		free (*stock);
		*stock = tmp;
	}
}

