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

void			ft_print_usage_error(char error);
static int 		ft_stock_commands(char command, int command_options);

static int		ft_check_file_errors(char **folder)
{
	struct stat *buffstatt;

	while (folder)
	{
		while (*folder)
		{
			buffstatt = malloc(sizeof(stat));
			if (stat(*folder, buffstatt) == -1)
			{
				ft_putstr("ft_ls : ");
				ft_putstr(*folder);
				ft_putstr(": No such file or directory\n");
				return (1);
			}
			free(buffstatt);
		}
		folder++;
	}
	return (0);
}

int				ft_check_usage(char ***av)
{
	int	command_options;

	command_options = 0;
	++*av;
	while (*av)
	{
		if (***av && ***av == '-')
		{
			++**av;
			if (***av == '-')
				return (command_options);
			while (***av)
			{
				if (ft_stock_commands(***av, command_options))
					command_options = ft_stock_commands(***av, command_options);
				else
				{
					ft_print_usage_error(***av);
					return (-1);
				}
				ft_putnbr(command_options);
				++**av;
			}
		}
		else
			return (command_options); 
		++*av;
		printf("%s\n", "coucou");
	}
	printf("%s\n", "exit");
	return (command_options);
}

int 		ft_stock_commands(char command, int command_options)
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

void			ft_print_usage_error(char error)
{
	ft_putstr("ls: illegal option -- ");
	ft_putchar(error);
	ft_putchar('\n');
	ft_putstr("usage: ls [-lRart] [file ...]");
}

int				main(int ac, char **av)
{
	int command_options;

	command_options = 0;
	ac++;
	command_options = ft_check_usage(&av);
	ft_check_file_errors(av);
	//ls();
	return (0);
}
