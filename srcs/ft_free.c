/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 14:43:44 by lazrossi          #+#    #+#             */
/*   Updated: 2017/07/10 14:44:19 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ft_free(t_ls **stock)
{
	t_ls *tmp;
	while (*stock)
	{
		tmp = (*stock)->next;
		free((*stock)->name);
		ft_memdel((void**)stock);
		*stock = tmp;
	}
}
