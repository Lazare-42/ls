#include "ls.h"

int				ft_check_usage(char ***av)
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

int		ft_check_file_errors(char **folder)
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

int 		ft_stock_commands(char command, int command_options)
{
	if (command == 'l' || command == 'R' || command == 'a'
			|| command == 'r' || command == 't' || command == 'u'
			|| command == 'f' || command == 'g' || command == 'S' 
			|| command == 'U' || command == '1' )
	{
		if (command == 'l')
			command_options = command_options | CMD_l;
		if (command == 'R')
			command_options = command_options | CMD_R;
		if (command == 'a' || command == 'f')
			command_options = command_options | CMD_a;
		if (command == 'r')
			command_options = command_options | CMD_r;
		if (command == 't')
			command_options = command_options | CMD_t;
		if (command == 'u')
			command_options = command_options | CMD_u;
		if (command == 'g')
			command_options = command_options | CMD_g;
		if (command == 'S')
			command_options = command_options | CMD_S;
		if (command == 'U')
			command_options = command_options | CMD_U;
		if (command == '1')
			command_options = command_options | CMD_1;
	}
	else
		return (0);
	return (command_options);
}
