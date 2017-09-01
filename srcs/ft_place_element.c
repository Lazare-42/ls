/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_place_element.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:55:44 by lazrossi          #+#    #+#             */
/*   Updated: 2017/08/31 01:46:51 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		ft_sort_by_options(t_ls *stock, t_ls *next_stock, int sort_options)
{
	if (sort_options & CMD_T)
		return (stock->stat.st_mtimespec.tv_sec - next_stock->stat.st_mtimespec.tv_sec);
	else if (sort_options & CMD_LAST_ACCESS)
		return (stock->stat.st_atimespec.tv_sec - next_stock->stat.st_atimespec.tv_sec);
	else if (sort_options & CMD_S)
		return (stock->stat.st_size - next_stock->stat.st_size);
	else if (sort_options & CMD_U)
		return (stock->stat.st_birthtimespec.tv_sec - next_stock->stat.st_birthtimespec.tv_sec);
	else
		return (ft_strcmp(stock->name, next_stock->name));
}

int		ft_place_rev_elem(t_ls *stock, t_ls *next_stock, const char *foldername, int **max, int sort_options)
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
			return (ft_place_rev_elem(stock->left, next_stock, foldername, max, sort_options));
	}
	if (!stock->right)
	{
		stock->right = next_stock; 
		if (stock->color == 0)
			return (0);
		return (1);
	}
	else
		return (ft_place_rev_elem(stock->right, next_stock, foldername, max, sort_options));
}

int		ft_place_elem(t_ls *stock, t_ls *next_stock,
		const char *foldername, int **max, int sort_options)
{
	if (!(sort_options & CMD_REVERSE))
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
				return (ft_place_elem(stock->left, next_stock, foldername, max, sort_options));
		}
		if (!stock->right)
		{
			stock->right = next_stock; 
			if (stock->color == 0)
				return (0);
			return (1);
		}
		else
			return (ft_place_elem(stock->right, next_stock, foldername, max, sort_options));
	}
	else
		return (ft_place_rev_elem(stock, next_stock, foldername, max, sort_options));
	return (1);
}
