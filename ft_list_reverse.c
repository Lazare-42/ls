/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:14:10 by lazrossi          #+#    #+#             */
/*   Updated: 2017/03/30 10:30:09 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ft_ls_reverse(t_ls **begin_list)
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
		list = list->next;
		p->next = q;
		q = p;
	}
	*begin_list = p;
}
