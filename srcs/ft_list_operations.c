/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:44:14 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 20:42:19 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ft_free(t_ls **stock)
{
	t_ls *tmp;

	if ((*stock) && (*stock)->left)
		ft_free(&(*stock)->left);
	if (*stock)
	{
		tmp = (*stock)->left;
		free((*stock)->name);
		ft_memdel((void**)stock);
		*stock = tmp;
	}
	if ((*stock) && (*stock)->right)
		ft_free(&(*stock)->right);
}

void	ft_cmd_reverse(t_ls **begin_list)
{
	t_ls*list;
	t_ls*q;
	t_ls*p;

	list = *begin_list;
	p = NULL;
	q = NULL;
	while (list)
	{
		p = list;
		list = list->left;
		p->left = q;
		q = p;
	}
	*begin_list = p;
}
