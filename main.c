/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 14:14:42 by lazrossi          #+#    #+#             */
/*   Updated: 2017/06/28 17:58:29 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft.h"

static void		ft_check_folder_errors(char **folder)
{
	DIR *dir;
	int i;

	i = 0;
	while (folder[i])
	{
		if (!(dir = opendir(folder[i])))
		{
			ft_putstr("ft_ls : ");
			ft_putstr(folder[i]);
			ft_putstr(": No such file or directory");
		}
		else
			closedir(dir);
		i++;
	}
}

void			ft_print_error_msg(char error)
{
	ft_putstr("ls: illegal option --");
	ft_putchar(error);
	ft_putchar('\n');
	ft_putstr("usage: ls [-lRart] [file ...]");
}


static int 		ft_stock_commands(char *command)
{
	int i;
	int command_options;

	i = 0;
	command_options = 0;
	while (command[i])
	{
		if (command[i] == 'l' || command[i] == 'R' || command[i] == 'a'
				|| command[i] == 'r' || command[i] == 't')
		{
			if (command[i] == 'l')
				command_options = command_options & CMD_l;
			if (command[i] == 'R')
				command_options = command_options & CMD_R;
			if (command[i] == 'a')
				command_options = command_options & CMD_a;
			if (command[i] == 'r')
				command_options = command_options & CMD_r;
			if (command[i] == 't')
				command_options = command_options & CMD_t;
		}
		else 
		{
			ft_print_error_msg(command[i]);
			return (0);
		}
		i++;
	}
	return (command_options);
}

int				main(int ac, char **av)
{
	int i;
	int command_options;

	i = ac;
	command_options = 0;
	while (av[ac])
	{
		if (*av[ac] == '-')
		{
			if (!(command_options = ft_stock_commands(av[ac]) & command_options))
				return (0);
		}
		ac--;
	}
	ft_check_folder_errors(av);
	ls(av);
}
