/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 14:43:46 by lazrossi          #+#    #+#             */
/*   Updated: 2017/07/26 19:19:29 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ls(char *name, int options, int file_mode)
{
	t_ls *stock;
	DIR *dir;
	dir = NULL;
	int i;

	i = 1;
	if (file_mode && !(dir = opendir((const char *)name)))
	{
		ft_print_errors(name);
		return ;
	}
	stock = ft_store(name, dir,  options);
	(options & CMD_r) ? ft_CMD_r(&(stock)) : 0;;
	((options & CMD_l && (!(options & CMD_g)))) ? ft_CMD_l(stock, name, file_mode), i = 0 : 0;
	(options & CMD_g ) ? ft_CMD_g(stock, name, file_mode), i = 0 : 0;
	(i) ? ft_print_normal(stock) : 0;
	((options & CMD_l || options & CMD_g) && (!(options & CMD_R))) ? ft_putchar('\n') : 0;
	if (dir)
		closedir(dir);
	(stock) ? ((options & CMD_R) ? ft_CMD_R(stock, name, options) : 0) : 0;  
	ft_free(&stock);
}
