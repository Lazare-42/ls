/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 04:21:09 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 18:38:38 by lazrossi         ###   ########.fr       */
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

int		*ft_fillup_val(t_ls *stock, int *max, int sort_options)
{
	int				val;
	struct group	*grp;
	int				k;

	k = 0;
	if (stock && ((sort_options & CMD_L) || (sort_options & CMD_G)))
	{
		(stock->stat.st_nlink > max[0]) ? max[0] = stock->stat.st_nlink : 0;
		val = ( getpwuid(stock->stat.st_uid)) ?
			ft_strlen(getpwuid(stock->stat.st_uid)->pw_name) : 0;
		(val > max[1]) ? max[1] = val : 0;
		grp = getgrgid(stock->stat.st_gid);
		(grp) ? val = ((int)ft_strlen(grp->gr_name)) : 0;
		(val > max[2]) ? max[2] = val : 0;
		((int)stock->stat.st_size > max[3]) ?
			max[3] = (int)stock->stat.st_size : 0;
		max[4] = max[4] + stock->stat.st_blocks;
		stock->name_len = 0;
	}
	else
	{
		stock->name_len = ft_strlen(stock->name);
		(stock->name_len > max[0]) ? max[0] = stock->name_len : 0;
	}
	return (max);
}

int		*ft_max_size(t_ls *stock, int *max, int sort_options)
{
	max = ft_fillup_val(stock, max, sort_options);
	return (max);
}
