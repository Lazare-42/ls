/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_normal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 14:03:25 by lazrossi          #+#    #+#             */
/*   Updated: 2017/08/10 14:05:44 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <sys/ioctl.h>

int		ft_longest_name(t_ls *stock)
{
	int		i;
	t_ls	*tmp;

	i = 0;
	tmp = stock;
	while (tmp)
	{
		i = ((int)ft_strlen(tmp->name) > i) ? (int)ft_strlen(tmp->name) : i;
		tmp = tmp->left;
	}
	return (i);
}

void	ft_print_normal(t_ls *stock)
{
	t_ls			*tmp;
	struct winsize	max;
	int				i;
	int				maxx;
	int				j;

	j = 0;
	maxx = 0;
	i = ft_longest_name(stock);
	tmp = stock;
	ioctl(1, TIOCGWINSZ, &max);
	if (tmp)
	{
		j = (int)ft_strlen(tmp->name);
		maxx += j;
		(maxx >= max.ws_col) ? ft_putchar('\n') : 0;
		(maxx >= max.ws_col) ? maxx = j : 0;
		ft_print_name(tmp->name, tmp->stat.st_mode);
		while (j++ <= i && ++maxx < max.ws_col && tmp->left)
			ft_putchar(' ');
		ft_putchar('\n');
		if (tmp->left)
			ft_print_normal(tmp->left);
		if (tmp->right)
			ft_print_normal(tmp->right);
	}
}
