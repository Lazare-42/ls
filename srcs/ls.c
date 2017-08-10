/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 14:43:46 by lazrossi          #+#    #+#             */
/*   Updated: 2017/08/10 17:00:47 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ls(char *name, int options, int file_mode)
{
	t_ls	*stock;
	DIR		*dir;
	int		i;

	i = 1;
	dir = NULL;
	(file_mode && !(dir = opendir((const char *)name))) ?
		ft_print_errors(name) : 0;
	if (file_mode && !(dir = opendir((const char *)name)))
		return ;
	stock = ft_store(name, dir, options);
	(options & CMD_REVERSE) ? ft_cmd_reverse(&(stock)) : 0;
	((options & CMD_L && (!(options & CMD_G)))) ?
		ft_cmd_l(stock, name, file_mode) : 0;
	((options & CMD_L && (!(options & CMD_G)))) ? i = 0 : 0;
	((options & CMD_L && (!(options & CMD_G)))) ? i = 0 : 0;
	(options & CMD_G) ? i = 0 : 0;
	(i && (!(options & CMD_1))) ? ft_print_normal(stock) : 0;
	(i && (options & CMD_1)) ? ft_cmd_1(stock) : 0;
	((options & CMD_L || options & CMD_G) && (!(options & CMD_R))) ?
		ft_putchar('\n') : 0;
	(dir) ? closedir(dir) : 0;
	(stock && (options & CMD_R)) ? ft_cmd_r(stock, name, options) : 0;
	(stock && (options & CMD_R)) ? ft_cmd_r(stock, name, options) : 0;
	ft_free(&stock);
}
