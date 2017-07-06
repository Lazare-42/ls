/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 01:51:31 by lazrossi          #+#    #+#             */
/*   Updated: 2017/07/04 01:51:33 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft.h"
#include <sys/xattr.h>
#include <pwd.h>
#include <time.h>
#include "ls.h"

t_ls	*ft_new_elem(char *name)
{
	t_ls	*tmp;

	if (!(tmp = malloc(sizeof(t_ls))))
		exit(1);
	tmp->name = ft_strdup(name);
	return (tmp);
}

t_ls	*ft_place_elem(char *name, const char *dirname, t_ls *stock)
{
	t_ls *new;
	t_ls *check;
	char *path;

	new = ft_new_elem(name);
	path = ft_strjoin((char*)dirname, "/");
	path = ft_strjoin(path, name);
	if (!stock)
	{
	stat(path, &(new->stat));
			return (new);
	}
	check = stock;
	while (check && check->next && ft_strcmp(check->next->name, new->name) < 0)
		check = check->next;
	new->next = check->next;
	check->next = new;
	stat(path, &(new->stat));
	return (stock);
}

t_ls	*ft_store(char *foldername)
{
	t_ls	*stock = NULL;
	DIR *dir;
	struct dirent *dent;
	dir = opendir(foldername);

	if(dir != NULL)
	{
		while((dent = readdir(dir)) != NULL)
			stock = ft_place_elem(dent->d_name, foldername, stock);
	}
	closedir(dir);
	return (stock);
}
