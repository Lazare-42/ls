/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 14:14:42 by lazrossi          #+#    #+#             */
/*   Updated: 2017/07/26 20:03:16 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft.h"

static void			ft_print_usage_error(char error);
static int 		ft_stock_commands(char command, int command_options);

static int		ft_check_file_errors(char *folder, int print_option)
{
	struct stat buffstatt;

	if (lstat(folder, &buffstatt))
	{
		if (print_option)
		{
		ft_putstr("ft_ls: ");
		ft_putstr(folder);
		ft_putstr(": No such file or directory\n");
		}
		return (0);
	}
	return (1);
}

static int				ft_check_usage(char ***av)
{
	int	command_options;

	command_options = 0;
	++*av;
	while (*av)
	{
		if (**av && ***av == '-')
		{
			if (**av && *(**av + 1) == '-')
				return (command_options);
			++**av;
			while (***av)
			{
				if (ft_stock_commands(***av, command_options))
					command_options = ft_stock_commands(***av, command_options);
				else
					return (-1);
				++**av;
			}
		}
		else
			return (command_options); 
		++*av;
	}
	return (command_options);
}

static int 		ft_stock_commands(char command, int command_options)
{
	if (command == 'l' || command == 'R' || command == 'a'
			|| command == 'r' || command == 't')
	{
		if (command == 'l')
			command_options = command_options | CMD_l;
		if (command == 'R')
			command_options = command_options | CMD_R;
		if (command == 'a')
			command_options = command_options | CMD_a;
		if (command == 'r')
			command_options = command_options | CMD_r;
		if (command == 't')
			command_options = command_options | CMD_t;
	}
	else 
		return (0);
	return (command_options);
}

static void			ft_print_usage_error(char error)
{
	ft_putstr("ls: illegal option -- ");
	ft_putchar(error);
	ft_putchar('\n');
	ft_putstr("usage: ls [-lRart] [file ...]");
	ft_putchar('\n');
}

int				main(int ac, char **av)
{
	int command_options;
	char **tmp;

	command_options = 0;
	ac++;
	if ((command_options = ft_check_usage(&av)) == -1)
	{
		ft_print_usage_error(**av);
		return (-1);
	}
	if (*av && !(ft_strcmp(*av, "--")))
		av++;
	if (*av)
	{
		tmp = av;
		while (*tmp)
		{
			ft_check_file_errors(*tmp, 1);
			tmp++;
		}
		while (*av)
		{
			if (ft_check_file_errors(*av, 0))
				ls(*av, command_options);
			av++;
		}
		return (0);
	}
	else
		ls(".", command_options);
	return (0);
}
