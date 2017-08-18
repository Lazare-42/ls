/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:45:32 by lazrossi          #+#    #+#             */
/*   Updated: 2017/08/18 15:21:06 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/xattr.h>
#include "ls.h"
#include <pwd.h>
#include <time.h>
#include <grp.h>

void	ft_put_whites(int max_str_len, int fillup, int options)
{
	char *tmp;

	tmp = NULL;
	if (options == 1 || options == 4)
	{
		tmp = ft_itoa(fillup);
		fillup = ft_strlen(tmp);
		ft_strdel(&tmp);
	}
	while (fillup < max_str_len)
	{
		ft_putchar(' ');
		fillup++;
	}
	(options != 3) ? ft_putchar(' ') : 0;
	if (options != 1 && options != 3)
		ft_putchar(' ');
}

int		*ft_new_int_tab(int *new)
{
	new[0] = 0;
	new[1] = 0;
	new[2] = 0;
	new[3] = 0;
	return (new);
}

int		*ft_fillup_val(t_ls *stock, int *max)
{
	int				val;
	t_ls			*tmp;
	struct group	*grp;

	tmp = stock;
	if (tmp)
	{
		(tmp->stat.st_nlink > max[0]) ? max[0] = tmp->stat.st_nlink : max[0];
		val = ft_strlen(getpwuid(tmp->stat.st_uid)->pw_name);
		(val > max[1]) ? max[1] = val : max[1];
		grp = getgrgid(tmp->stat.st_gid);
		(grp) ? val = ((int)ft_strlen(grp->gr_name)) : 0;
		(val > max[2]) ? max[2] = val : max[2];
		((int)tmp->stat.st_size > max[3]) ? max[3] = (int)tmp->stat.st_size : max[3];
	}
	return (max);
}

int		*ft_max_size(t_ls *stock, int *max)
{
	char	*len;
	t_ls	*tmp;


	tmp = stock;
	//	(!max) ? max = ft_memalloc(sizeof(int) * 4) : 0;
	max = malloc(sizeof(int) * 4);
	max = ft_new_int_tab(max);
	max = ft_fillup_val(stock, max);
	len = ft_itoa(max[0]);
	max[0] = ft_strlen(len);
	ft_strdel(&len);
	len = ft_itoa(max[3]);
	max[3] = ft_strlen(len);
	ft_strdel(&len);
	return (max);
}
