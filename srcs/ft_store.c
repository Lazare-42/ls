/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 01:51:31 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/28 16:55:56 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ls.h"
#include "../libft/include/libft.h"
#include <sys/xattr.h>
#include <pwd.h>
#include <time.h>
#include "../includes/ls.h"

t_ls	*ft_new_elem(char *name, const char *foldername,
		int **max_padding, int sort_options)
{
	t_ls *new;
	char *path;

	path = NULL;
	if (!(name))
		return (NULL);
	if (!(new = malloc(sizeof(t_ls))))
		exit(1);
	new->left = NULL;
	new->right = NULL;
	new->color = 0;
	new->name = ft_strdup(name);
	(foldername) ? path = find_path(name, (char*)foldername) : 0;
	(!(foldername)) ? path = name : 0;
	if (lstat(path, &(new->stat)))
	{
		(path && ft_strcmp(name, path) != 0) ? ft_strdel(&path) : 0;
		ft_print_errors(new->name);
		ft_strdel(&(new->name));
		ft_memdel((void**)new);
		return (NULL);
	}
	*max_padding = ft_max_size(new, *max_padding, sort_options);
	(path && ft_strcmp(name, path) != 0) ? ft_strdel(&path) : 0;
	return (new);
}

int		*ft_store_folder(char *foldername, int *max, t_ls **stock, DIR *dir)
{
	struct dirent	*dent;
	t_ls			*new_stock;

	while ((dir && (dent = readdir(dir))))
	{
		(!(max[5] & CMD_A) && dent->d_name[0] == '.') ?
			dent = NULL : 0;
		if (dent && !(*stock))
		{
			(*stock) = ft_new_elem(dent->d_name, foldername,
					&max, max[5]);
			((*stock)) ? (*stock)->color = 1 : 0;
		}
		else if (dent)
		{
			if (!(new_stock = ft_new_elem(dent->d_name, foldername,
					&max, max[5])))
				return (max);
			if (!(ft_place_elem((*stock), new_stock, &max, max[5])))
				ft_rotate(stock, new_stock, max[5]);
		}
	}
	return (max);
}

int		*ft_store(char *foldername, DIR *dir, int sort_options, t_ls **stock)
{
	int				*max;

	if (!(max = (int*)ft_memalloc(sizeof(int) * 7)))
		exit(1);
	max[5] = sort_options;
	if (dir != NULL)
		max = ft_store_folder(foldername, max, stock, dir);
	else
		(*stock) = ft_new_elem(foldername, NULL, &max, sort_options);
	return (max);
}
