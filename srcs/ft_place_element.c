/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_place_element.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:55:44 by lazrossi          #+#    #+#             */
/*   Updated: 2017/08/17 20:32:41 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		ft_place_elem(t_ls *stock, char *name, const char *foldername)
{
	if (ft_strcmp(stock->name, name) > 0)
	{
		if (!stock->left)
		{
			stock->left = ft_new_elem(name, foldername); 
			if (stock->color == 0)
				return (0);
			return (1);
		}
		else
			return (ft_place_elem(stock->left, name, foldername));
	}
	else if (ft_strcmp(stock->name, name) < 0)
	{
		if (!stock->right)
		{
			stock->right = ft_new_elem(name, foldername); 
			if (stock->color == 0)
				return (0);
			return (1);
		}
		else
			return (ft_place_elem(stock->right, name, foldername));
	}
	return (1);
}
