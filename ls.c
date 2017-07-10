/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 14:43:46 by lazrossi          #+#    #+#             */
/*   Updated: 2017/07/10 14:43:47 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft.h"

void	ls(char *name, int options)
{
	t_ls *stock;

	stock = ft_store(name);
	(options & CMD_a) ? stock : ft_advance_stock_if_no_a(&stock);
	(options & CMD_r) ? ft_ls_reverse(&(stock)) : stock;
	(options & CMD_l) ? ft_CMD_r(stock) : ft_print_normal(stock);
	//ft_free(&stock);
	ft_putchar('\n');
}
