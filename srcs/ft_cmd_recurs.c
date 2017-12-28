/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_recurs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 16:51:06 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/28 16:54:27 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"

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

void			ft_cmd_recurs(t_ls *stock, char *name, int options)
{
	t_ls	*tmp;
	char	*new_name;

	new_name = NULL;
	tmp = stock;
	if (tmp)
	{
		if (tmp->left)
			ft_cmd_recurs(tmp->left, name, options);
		if (S_ISDIR(tmp->stat.st_mode) && ft_strcmp("..", tmp->name)
				&& ft_strcmp(".", tmp->name))
			ft_print_and_send(name, options, tmp, new_name);
		if (tmp->right)
			ft_cmd_recurs(tmp->right, name, options);
	}
}
