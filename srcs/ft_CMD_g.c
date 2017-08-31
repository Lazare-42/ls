/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 15:30:17 by lazrossi          #+#    #+#             */
/*   Updated: 2017/08/31 05:57:21 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <sys/xattr.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int		ft_cmd_g(t_ls *tmp, char *foldername, int *max_size, int first)
{
	time_t	local_time;
	char	*path;
	t_ls	*stock;

	stock = tmp;
	local_time = time(&local_time);
	(!stock) ? ft_putchar('\n') : 0;
	if (first)
	{
		ft_putstr("totaliiiiiiiiiiiiiiiiiiiiii ");
		ft_putnbr(max_size[4]);

	}
	ft_putchar('\n');
	if (stock)
	{
		path = find_path(stock->name, foldername);
		ft_print_rights(stock, path);
		ft_putstr("couco");
		//ft_print_grp_usr(stock, max_size);
		ft_print_time(stock, local_time);
		ft_putchar(' ');
		ft_print_name(stock->name, stock->stat.st_mode);
		(S_ISLNK(stock->stat.st_mode)) ? print_lnkabout(path) : 0;
		ft_memdel((void**)&path);
		if (stock->left)
			ft_cmd_g(stock->left, foldername, max_size, 0);
		if (stock->right)
			ft_cmd_g(stock->right, foldername, max_size, 0);
	}
	return (1);
}
