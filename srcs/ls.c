/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 14:43:46 by lazrossi          #+#    #+#             */
/*   Updated: 2017/08/10 19:59:58 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		*ft_adapt_padding_size(int *max)
{
	char	*len;

	len = ft_itoa(max[0]);
	max[0] = ft_strlen(len);
	ft_strdel(&len);
	len = ft_itoa(max[3]);
	max[3] = ft_strlen(len);
	ft_strdel(&len);
	return (max);
}

void	ls(char *name, int options, int file_mode)
{
	t_ls	*stock;
	t_ls    *tmp;
	DIR		*dir;
	int		i;
	int		*max;

	i = 1;
	dir = NULL;
	stock = NULL;;
	if (file_mode && !(dir = opendir((const char *)name)))
	{
		ft_print_errors(name);
		return ;
	}
	max = ft_store(name, dir, options, &stock);
	(options & CMD_REVERSE) ? ft_cmd_reverse(&(stock)) : 0;
	tmp = stock;
	max = ft_adapt_padding_size(max);
	((options & CMD_L && (!(options & CMD_G)))) ?
		ft_cmd_l(tmp, name, max, 1) : 0;
	((options & CMD_L && (!(options & CMD_G)))) ? i = 0 : 0;
	(options & CMD_G) ? i = 0 : 0;
	(options & CMD_G) ? ft_cmd_g(stock, name, file_mode) : 0;
	(i && (!(options & CMD_1))) ? ft_print_normal(stock) : 0;
	(i && (options & CMD_1)) ? ft_cmd_1(stock) : 0;
	((options & CMD_L || options & CMD_G) && (!(options & CMD_R))) ?
		ft_putchar('\n') : 0;
	(dir) ? closedir(dir) : 0;
	((options & CMD_R) ? ft_cmd_r(stock, name, options) : 0);
	ft_free(&stock);
}
