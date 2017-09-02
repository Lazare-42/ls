/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:50:16 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 02:56:21 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		ft_check_usage(char ***av)
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

void	ft_check_file_errors(char **folder)
{
	struct stat buffstatt;

	while (folder && *folder)
	{
		if (lstat(*folder, &buffstatt))
			ft_print_errors(*folder);
		folder++;
	}
}

int		ft_stock_commands(char command, int command_options)
{
	if (command == 'l' || command == 'R' || command == 'a'
			|| command == 'r' || command == 't' || command == 'u'
			|| command == 'f' || command == 'g' || command == 'S'
			|| command == 'U' || command == '1')
	{
		(command == 'l') ? command_options = command_options | CMD_L : 0;
		(command == 'R') ? command_options = command_options | CMD_R : 0;
		(command == 'a' || command == 'f') ?
			command_options = command_options | CMD_A : 0;
		(command == 'r') ? command_options = command_options | CMD_REVERSE : 0;
		(command == 't') ? command_options = command_options | CMD_T : 0;
		(command == 'u') ?
			command_options = command_options | CMD_LAST_ACCESS : 0;
		(command == 'g') ? command_options = command_options | CMD_G : 0;
		(command == 'S') ? command_options = command_options | CMD_S : 0;
		(command == 'U') ? command_options = command_options | CMD_U : 0;
		(command == '1') ? command_options = command_options | CMD_1 : 0;
	}
	else
		return (0);
	return (command_options);
}
