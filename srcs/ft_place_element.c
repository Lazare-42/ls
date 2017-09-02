/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_place_element.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:55:44 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 05:08:34 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <stdio.h>

static int		ft_sort_by_rev_options(t_ls *stock,
		t_ls *next_stock, int sort_options)
{
	if (sort_options & CMD_T)
		return (next_stock->stat.st_mtimespec.tv_sec
				- stock->stat.st_mtimespec.tv_sec);
	else if (sort_options & CMD_LAST_ACCESS)
		return (next_stock->stat.st_atimespec.tv_sec
				- stock->stat.st_atimespec.tv_sec);
	else if (sort_options & CMD_S)
		return (next_stock->stat.st_size
				- stock->stat.st_size);
	else if (sort_options & CMD_U)
		return (next_stock->stat.st_birthtimespec.tv_sec
				- stock->stat.st_birthtimespec.tv_sec);
	else
		return (ft_strcmp(stock->name, next_stock->name));
}

int				ft_sort_by_options(t_ls *stock,
		t_ls *next_stock, int sort_options)
{
	if (!(sort_options & CMD_REVERSE))
	{
		if (sort_options & CMD_T)
			return (stock->stat.st_mtimespec.tv_sec -
					next_stock->stat.st_mtimespec.tv_sec);
		else if (sort_options & CMD_LAST_ACCESS)
			return (stock->stat.st_atimespec.tv_sec -
					next_stock->stat.st_atimespec.tv_sec);
		else if (sort_options & CMD_S)
			return (stock->stat.st_size -
					next_stock->stat.st_size);
		else if (sort_options & CMD_U)
			return (stock->stat.st_birthtimespec.tv_sec -
					next_stock->stat.st_birthtimespec.tv_sec);
		else
			return (ft_strcmp(next_stock->name, stock->name));
	}
	return (ft_sort_by_rev_options(stock, next_stock, sort_options));
}

int				ft_place_elem(t_ls *stock, t_ls *next_stock,
		int **max, int sort_options)
{
	if (ft_sort_by_options(stock, next_stock, sort_options) <= 0)
	{
		if (!stock->left)
		{
			stock->left = next_stock;
			if (stock->color == 0)
				return (0);
			return (1);
		}
		else
			return (ft_place_elem(stock->left, next_stock,
						max, sort_options));
	}
	if (!stock->right)
	{
		stock->right = next_stock;
		if (stock->color == 0)
			return (0);
		return (1);
	}
	else
		return (ft_place_elem(stock->right, next_stock,
					max, sort_options));
}
