/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 14:14:42 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/01 15:17:26 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static	void	ft_send_folders_to_ls(char **name, int command_options, int j)
{
	struct stat buffstatt;

	while (name && *name)
	{
		if (!(lstat(*name, &buffstatt)))
		{
			if (buffstatt.st_mode & S_IFDIR)
			{
				(j) ? ft_putstr(*name) : 0;
				(j) ? ft_putstr(":\n") : 0;
				ls(*name, command_options, 1);
			}
		}
		++name;
		(j && *name) ? ft_putchar('\n') : 0;
	}
}

static	void	ft_send_files_to_ls(char **folder, int command_options)
{
	struct stat	buffstatt;
	char		**name;
	int			j;

	name = folder;
	j = 0;
	name++;
	(*name) ? j = 1 : 0;
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
	ft_send_folders_to_ls(name, command_options, j);
}

int				main(int ac, char **av)
{
	int		command_options;
	char	**tmp;

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
