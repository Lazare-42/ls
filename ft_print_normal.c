/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_normal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 14:03:25 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 15:59:17 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <sys/ioctl.h>
#include <stdio.h>

void	ft_proper_print(t_ls *tmp, int max_ws_col,
		int max_stock_val, int *total_written, int inode_option)
{
	int i;

	i = max_stock_val;
	if (tmp && tmp->name)
	{
		if (tmp->left)
			ft_proper_print(tmp->left,
					max_ws_col, max_stock_val, total_written, inode_option);
		*total_written += max_stock_val + max_stock_val;
		*total_written += (inode_option) ? 8 : 0;
		(*total_written >= max_ws_col) ? ft_putchar('\n') : 0;
		if (inode_option)
		{
			ft_putnbr(tmp->stat.st_ino);
			ft_putchar(' ');
		}
		(*total_written >= max_ws_col) ? *total_written = 0 : 0;
		ft_print_name(tmp->name, tmp->stat.st_mode);
		while (i-- - tmp->name_len >= 0)
			ft_putchar(' ');
		if (tmp->right)
			ft_proper_print(tmp->right,
					max_ws_col, max_stock_val, total_written, inode_option);
	}
}

void	ft_print_name(char *name, int st_mode)
{
	if (S_ISDIR(st_mode))
	{
		ft_putstr("\e[0;96m");
		ft_putstr(name);
		ft_putstr("\e[0m");
	}
	else if (S_ISLNK(st_mode))
	{
		ft_putstr("\033[0;35m");
		ft_putstr(name);
		ft_putstr("\e[0m");
	}
	else if (st_mode & S_IXUSR)
	{
		ft_putstr("\033[0;31m");
		ft_putstr(name);
		ft_putstr("\e[0m");
	}
	else
		ft_putstr(name);
}

void	ft_print_normal(t_ls *stock, int max_stock_val, int sort_options)
{
	t_ls			*tmp;
	struct winsize	max;
	int				maxx_ws_col;
	int				total_written;

	tmp = stock;
	ioctl(1, TIOCGWINSZ, &max);
	maxx_ws_col = max.ws_col;
	total_written = 0;
	if (sort_options & CMD_L)
		ft_proper_print(tmp, maxx_ws_col, max_stock_val, &total_written, 1);
	else
		ft_proper_print(tmp, maxx_ws_col, max_stock_val, &total_written, 1);
	ft_putchar('\n');
}