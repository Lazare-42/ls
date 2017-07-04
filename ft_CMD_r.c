/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CMD_r.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 01:51:23 by lazrossi          #+#    #+#             */
/*   Updated: 2017/07/04 03:20:12 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ls.h"
#include "ls.h"
#include "libft.h"
#include <pwd.h>
#include <time.h>
#include "ls.h"
#include "libft.h"
#include "libft.h"

int		ft_CMD_r(t_ls *stock)
{
	char *time;

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
		ft_putstr("   ");     
		ft_putchar(stock->stat.st_nlink);
		ft_putstr(getpwuid(stock->stat.st_uid)->pw_name);
		ft_putstr("   ");     
		ft_putnbr((int)stock->stat.st_size);
		time = ft_strsub(ctime(&(stock->stat.st_mtime)), 4, 12);
		ft_putstr("  ");
		ft_putstr(time);
		ft_putstr(stock->name);
		ft_putchar('\n');
		stock = stock->next;
	}
	return (1);
}
