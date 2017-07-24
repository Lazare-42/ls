/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 14:43:46 by lazrossi          #+#    #+#             */
/*   Updated: 2017/07/12 08:42:08 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft.h"

void	ls(char *name, int options)
{
	t_ls *stock;
	DIR *dir;

	dir = NULL;
	dir = opendir(name);
	stock = (options & CMD_t) ? ft_store(name, dir,  1) : ft_store(name, dir,  0);
	stock = (options & CMD_a) ? stock : ft_advance_stock_if_no_a(stock, options);
	(options & CMD_r) ? ft_CMD_r(&(stock)) : stock;
	(options & CMD_l) ? ft_CMD_l(stock, name) : ft_print_normal(stock);
	if (dir)
		closedir(dir);
	ft_putchar('\n');
	if (options & CMD_R)
		ft_putchar('\n');
	(options & CMD_R) ? ft_CMD_R(stock, name, options) : options;
	//ft_free(&stock);
}
