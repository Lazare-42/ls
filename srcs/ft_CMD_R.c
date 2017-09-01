/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_r.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:41:23 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/01 15:17:25 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static	void	ft_print_and_send(char *name,
		int options, t_ls *stock, char *new_name)
{
	char *add_slash;

	add_slash = ft_strjoin(name, "/");
	new_name = ft_strjoin(add_slash, stock->name);
	ft_putchar('\n');
	ft_putstr(new_name);
	ft_putstr(":");
	ft_putchar('\n');
	ls(new_name, options, 1);
	ft_memdel((void**)&(new_name));
	ft_memdel((void**)&(add_slash));
}

void			ft_cmd_r(t_ls *stock, char *name, int options)
{
	t_ls	*tmp;
	char	*new_name;
	int		i;

	i = 1;
	new_name = NULL;
	tmp = stock;
	while (tmp)
	{
		if (i)
			ft_putchar('\n');
		if (S_ISDIR(tmp->stat.st_mode) && ft_strcmp("..", tmp->name)
				&& ft_strcmp(".", tmp->name))
			ft_print_and_send(name, options, tmp, new_name);
		tmp = tmp->next;
		i = 0;
	}
}
