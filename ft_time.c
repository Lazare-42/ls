#include "ls.h"
#include <time.h>
#include "libft.h"
	
void	ft_time(t_ls *stock)
{

	t_ls *tmp;
	char *time;

	tmp = stock;
	//char *date_of_birth;
	while (tmp)
	{
		//date_of_birth = ft_strcpy(date_of_birth, (&ctime((stock->stat.st_mtime))));
			time = ctime(&(stock->stat.st_mtime));
		ft_putstr(time);
		//ft_putchar('\n');
		tmp = tmp->next;
	}
}
