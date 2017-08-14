/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_place_element.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:55:44 by lazrossi          #+#    #+#             */
/*   Updated: 2017/08/10 16:46:34 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_ls	*ft_place_elem(t_ls **stock, char *name, const char *foldername)
{
	if (*stock == NULL)
		*stock = ft_new_elem(name, foldername); 
	else if (ft_strcmp((*stock)->name, name) > 0)
		ft_place_elem(&(*stock)->left, name, foldername);
	else if (ft_strcmp((*stock)->name, name) < 0)
		ft_place_elem(&(*stock)->right, name, foldername);
	return (*stock);
}
