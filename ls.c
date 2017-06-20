/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 19:08:21 by lazrossi          #+#    #+#             */
/*   Updated: 2017/06/19 18:39:23 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft.h"

int	ft_store(char *foldername, t_ls	**stock)
{
	DIR *dir;
	struct dirent *dent;
	dir = opendir(foldername);
	t_ls *tmp;

	if(dir != NULL)
	{
			while((dent = readdir(dir)) != NULL)
			{
				if (!(stock))
				{
					*stock = malloc(sizeof(t_ls));
					(*stock)->next = NULL;
				}
				else 
				{
					tmp = malloc(sizeof(t_ls));
					tmp->next = *stock;
					*stock = tmp;
				}
				(*stock)->name = ft_strnew(ft_strlen(dent->d_name));
				(*stock)->name = ft_strdup(dent->d_name);
				stat((*stock)->name, &((*stock)->stat));
		}
		if (closedir(dir))
			return (-1);
	}
	return (0);
}

void ft_print_normal(t_ls *stock)
{
	while (stock && stock->next)
	{
		printf("%s\n", (stock)->name);
		stock = (stock)->next;
	}
	if (stock)
		printf("%s\n", (stock)->name);
}

int main()
{
	t_ls *stock = NULL;
	ft_store(".", &stock);
	ft_print_normal(stock);
	return (0);
}
