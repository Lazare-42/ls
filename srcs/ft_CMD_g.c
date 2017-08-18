/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_g.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 15:44:10 by lazrossi          #+#    #+#             */
/*   Updated: 2017/08/10 17:07:02 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <grp.h>
#include <time.h>

void	ft_print_grp(t_ls *stock, int *max_size)
{
	struct group *grp;

	ft_put_whites(max_size[0], stock->stat.st_nlink, 1);
	ft_putnbr(stock->stat.st_nlink);
	ft_putchar(' ');
	grp = getgrgid(stock->stat.st_gid);
	if (grp)
	{
		ft_putstr(grp->gr_name);
		ft_put_whites(max_size[2], ft_strlen(grp->gr_name), 3);
		ft_put_whites(max_size[3], stock->stat.st_size, 4);
		ft_putnbr((int)stock->stat.st_size);
		ft_putchar(' ');
		return ;
	}
	ft_putstr(strerror(errno));
	ft_put_whites(max_size[2], ft_strlen(strerror(errno)), 3);
}

int			ft_cmd_g(t_ls *tmp, char *foldername, int file_mode)
{
	//int		*max_size;
	time_t	local_time;
	char	*path;
	t_ls	*stock;

	file_mode++;
	stock = tmp;
	//max_size = ft_max_size(stock);
	local_time = time(&local_time);
	(!stock) ? ft_putchar('\n') : 0;
	while (stock)
	{
		path = find_path(stock->name, foldername);
		ft_print_rights(stock, path);
		//ft_print_grp(stock, max_size);
		ft_print_time(stock, local_time);
		ft_putchar(' ');
		ft_print_name(stock->name, stock->stat.st_mode);
		(S_ISLNK(stock->stat.st_mode)) ? print_lnkabout(path) : 0;
		(stock->left) ? ft_putchar('\n') : 0;
		stock = stock->left;
		ft_memdel((void**)&path);
	}
	//ft_memdel((void**)&max_size);
	return (1);
}
