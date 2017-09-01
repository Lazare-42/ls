/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:35:50 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/01 15:17:26 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ft_cmd_1(t_ls *stock)
{
	t_ls *tmp;

	tmp = stock;
	while (tmp)
	{
		ft_print_name(tmp->name, tmp->stat.st_mode);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}
