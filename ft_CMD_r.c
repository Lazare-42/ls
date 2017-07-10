/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CMD_r.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 01:51:23 by lazrossi          #+#    #+#             */
/*   Updated: 2017/07/10 16:40:48 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/xattr.h>
#include "ls.h"
#include "libft.h"
#include <pwd.h>
#include <time.h>

void	ft_put_whites(int max_str_len,int  fillup)
{
	fillup = ft_strlen(ft_itoa(fillup));
	while (fillup < max_str_len)
	{
		ft_putchar(' ');
		fillup++;
	}
}

int		ft_max_size(t_ls *stock)
{
	int max;
	t_ls *tmp;

	max = 0;
	tmp = stock;
	while (tmp)
	{
		(tmp->stat.st_nlink > max) ? max = tmp->stat.st_nlink : max;
		tmp = tmp->next;
	}
	max = ft_strlen(ft_itoa(max));
	return (max);
}

int		ft_CMD_r(t_ls *stock)
{
	char *time;
	int size;

	size = ft_max_size(stock);
	while (stock)
	{
		
		ft_putchar (S_ISDIR(stock->stat.st_mode) ? 'd' : '-');
		ft_putchar( (stock->stat.st_mode & S_IRUSR) ? 'r' : '-');
		ft_putchar( (stock->stat.st_mode & S_IWUSR) ? 'w' : '-');
		ft_putchar( (stock->stat.st_mode & S_IXUSR) ? 'x' : '-');
		ft_putchar( (stock->stat.st_mode & S_IRGRP) ? 'r' : '-');
		ft_putchar( (stock->stat.st_mode & S_IWGRP) ? 'w' : '-');
		ft_putchar( (stock->stat.st_mode & S_IXGRP) ? 'x' : '-');
		ft_putchar( (stock->stat.st_mode & S_IROTH) ? 'r' : '-');
		ft_putchar(' ');
		ft_put_whites(size, stock->stat.st_nlink);
		ft_putnbr(stock->stat.st_nlink);
		ft_putchar(' ');
		ft_putstr(getpwuid(stock->stat.st_uid)->pw_name);
		ft_putchar(' ');
		ft_putstr(
		ft_putstr("   ");     
		ft_putnbr((int)stock->stat.st_size);
		time = ft_strsub(ctime(&(stock->stat.st_mtime)), 4, 12);
		ft_putstr("  ");
		ft_putstr(time);
		ft_putchar(' ');
		ft_putstr(stock->name);
		ft_putchar('\n');
		stock = stock->next;
	}
	
	return (1);
}
