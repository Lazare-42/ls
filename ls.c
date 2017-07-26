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

	if (!(dir = opendir((const char *)name)))
		return ;
	stock = (options & CMD_t) ? ft_store(name, dir,  options) : ft_store(name, dir,  options);
	(options & CMD_r) ? ft_CMD_r(&(stock)) : stock;
	(options & CMD_l) ? ft_CMD_l(stock, name) : ft_print_normal(stock);
	if (dir)
		closedir(dir);
	ft_putchar('\n');
	(options & CMD_R) ? ft_CMD_R(stock, name, options) : options;
	ft_free(&stock);
}
