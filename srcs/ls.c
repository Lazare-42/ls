/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 14:43:46 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 18:14:29 by lazrossi         ###   ########.fr       */
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

void	pursue_ls(char *name, int options, int *max, t_ls *tmp)
{
	int		i;

	i = 1;
	((options & CMD_L && (!(options & CMD_G)))) ? i = 0 : 0;
	(options & CMD_G) ? i = 0 : 0;
	(i && (!(options & CMD_1))) ? ft_print_normal(tmp, max[0]) : 0;
	(i && (options & CMD_1)) ? ft_cmd_1(tmp) : 0;
	((options & CMD_L || options & CMD_G) && (!(options & CMD_R))) ?
		ft_putchar('\n') : 0;
	((options & CMD_R)) ? ft_putchar('\n') : 0;
	((options & CMD_R) ? ft_cmd_r(tmp, name, options) : 0);
}

void	ls(char *name, int options, int file_mode)
{
	t_ls	*stock;
	t_ls	*tmp;
	DIR		*dir;
	int		*max;

	dir = NULL;
	stock = NULL;
	if (file_mode && !(dir = opendir((const char *)name)))
	{
		ft_print_errors(name);
		return ;
	}
	max = ft_store(name, dir, options, &stock);
	(options & CMD_REVERSE) ? ft_cmd_reverse(&(stock)) : 0;
	tmp = stock;
	((options & CMD_G) ||
	(options & CMD_L)) ? max = ft_adapt_padding_size(max) : 0;
	((options & CMD_L && (!(options & CMD_G)))) ?
		ft_cmd_l(tmp, name, max, file_mode) : 0;
	(options & CMD_G) ? ft_cmd_g(tmp, name, max, file_mode) : 0;
	pursue_ls(name, options, max, tmp);
	(dir) ? closedir(dir) : 0;
	ft_free(&stock);
	while (1)
		tmp = stock;
}
