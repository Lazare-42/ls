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

static int 		ft_stock_commands(char command, int command_options);

static int		ft_check_file_errors(char **folder)
{
	struct stat buffstatt;

	while (folder && *folder)
	{
		if (lstat(*folder, &buffstatt))
		{
			ft_print_errors(*folder);
			return (0);
		}
		folder++;
	}
	return (1);
}

static void ft_send_files_to_ls(char **folder, int command_options)
{
	struct stat buffstatt;
	char **name;
	int j;

	name = folder;
	j = 0;
	name++;
	(*name) ? j = 1 :0;
	name = folder;
	while (folder && *folder)
	{
		if (!(lstat(*folder, &buffstatt)))
		{
			if (!(buffstatt.st_mode & S_IFDIR))
				ls(*folder, command_options, 0);
		}
		++folder;
	}
	while (name && *name)
	{
		if (!(lstat(*name, &buffstatt)))
		{
			if (buffstatt.st_mode & S_IFDIR)
			{
				(j) ? ft_putchar('\n'), ft_putstr(*name), ft_putstr(":\n") : 0;
				ls(*name, command_options, 1);
			}
		}
		++name;
	}
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
		ft_check_file_errors(tmp);
		ft_send_files_to_ls(av, command_options);
		return (0);
	}
	else
		ls(".", command_options, 1);
	return (0);
}
