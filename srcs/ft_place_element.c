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

int		ft_place_rev_elem(t_ls *stock, char *name, const char *foldername, int **max, int sort_options)
{
	if (ft_strcmp(stock->name, name) <= 0)
	{
		if (!stock->left)
		{
			stock->left = ft_new_elem(name, foldername, max, sort_options); 
			if (stock->color == 0)
				return (0);
			return (1);
		}
		else
			return (ft_place_rev_elem(stock->left, name, foldername, max, sort_options));
	}
	if (!stock->right)
	{
		stock->right = ft_new_elem(name, foldername, max, sort_options); 
		if (stock->color == 0)
			return (0);
		return (1);
	}
	else
		return (ft_place_rev_elem(stock->right, name, foldername, max, sort_options));
	return (1);
}

int		ft_place_elem(t_ls *stock, char *name, const char *foldername, int **max, int sort_options)
{
	if (!(sort_options & CMD_REVERSE))
	{
		if (ft_strcmp(stock->name, name) >= 0)
		{
			if (!stock->left)
			{
				stock->left = ft_new_elem(name, foldername, max, sort_options); 
				if (stock->color == 0)
					return (0);
				return (1);
			}
			else
				return (ft_place_elem(stock->left, name, foldername, max, sort_options));
		}
		if (!stock->right)
		{
			stock->right = ft_new_elem(name, foldername, max, sort_options); 
			if (stock->color == 0)
				return (0);
			return (1);
		}
		else
			return (ft_place_elem(stock->right, name, foldername, max, sort_options));
	}
	else
		return (ft_place_rev_elem(stock->left, name, foldername, max, sort_options));
	return (1);
}
