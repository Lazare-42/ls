#include <sys/xattr.h>
#include "ls.h"
#include "libft.h"
#include <pwd.h>
#include <time.h>
#include <grp.h>

void	ft_put_whites(int max_str_len,int  fillup, int options)
{
	if (options == 1 || options == 4)
		fillup = ft_strlen(ft_itoa(fillup));
	while (fillup <= max_str_len)
	{
		ft_putchar(' ');
		fillup++;
	}
	ft_putchar(' ');
}

int *ft_new_int_tab(int *new)
{
	new[0] = 0;
	new[1] = 0;
	new[2] = 0;
	new[3] = 0;
	return (new);
}

int	*ft_max_size(t_ls *stock)
{
	int *max;
	int val;
	struct group *grp;
	t_ls *tmp;
	int k;
	
	k = 0;
	max = malloc(sizeof(int) * 4);
	max = ft_new_int_tab(max);
	tmp = stock;
	while (tmp)
	{
		(tmp->stat.st_nlink > max[0]) ? max[0] = tmp->stat.st_nlink : max[0];
		val = ft_strlen(getpwuid(tmp->stat.st_uid)->pw_name);
		(val > max[1] )? max[1] = val : max[1]; 
		grp = getgrgid(tmp->stat.st_gid);
		val = ((int)ft_strlen(grp->gr_name));
		(val > max[2] )? max[2] = val : max[2];
		((int)tmp->stat.st_size > max[3]) ?  max[3] = (int)tmp->stat.st_size : max[3];
		k = k + tmp->stat.st_blocks;
		tmp = tmp->next;
	}
	max[0] = ft_strlen(ft_itoa(max[0]));
	max[3] = ft_strlen(ft_itoa(max[3]));
	ft_putstr("total ");
	ft_putnbr(k);
	return (max);
}
