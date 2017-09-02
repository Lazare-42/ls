/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_normal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 14:03:25 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 05:09:38 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <sys/ioctl.h>
#include <stdio.h>

void	ft_proper_print(t_ls *tmp, int max_ws_col,
		int max_stock_val, int *total_written)
{
	int i;

	i = max_stock_val;
	if (tmp && tmp->name)
	{
		if (tmp->left)
			ft_proper_print(tmp->left,
					max_ws_col, max_stock_val, total_written);
		*total_written += max_stock_val + max_stock_val;
		(*total_written >= max_ws_col) ? ft_putchar('\n') : 0;
		(*total_written >= max_ws_col) ? *total_written = 0 : 0;
		ft_print_name(tmp->name, tmp->stat.st_mode);
		while (i-- - tmp->name_len >= 0)
			ft_putchar(' ');
		if (tmp->right)
			ft_proper_print(tmp->right,
					max_ws_col, max_stock_val, total_written);
	}
}

void	ft_print_normal(t_ls *stock, int max_stock_val)
{
	t_ls			*tmp;
	struct winsize	max;
	int				maxx_ws_col;
	int				total_written;

	tmp = stock;
	ioctl(1, TIOCGWINSZ, &max);
	maxx_ws_col = max.ws_col;
	total_written = 0;
	ft_proper_print(tmp, maxx_ws_col, max_stock_val, &total_written);
}
