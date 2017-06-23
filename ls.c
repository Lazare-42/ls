/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 19:08:21 by lazrossi          #+#    #+#             */
/*   Updated: 2017/06/23 18:07:08 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft.h"

int ft_print_normal(t_ls *stock);
void	ls(char *name);

t_ls	*ft_store(char *foldername)
{
	t_ls	*stock = NULL;
	DIR *dir;
	struct dirent *dent;
	dir = opendir(foldername);
	t_ls *tmp;

	if(dir != NULL)
	{
		while((dent = readdir(dir)) != NULL)
		{
			tmp = malloc(sizeof(t_ls));
			tmp->next = stock;
			stock = tmp;
			(stock)->name = ft_strdup(dent->d_name);
			stat(stock->name, &(stock->stat));
		}
	}
	ft_print_normal(stock);
	return (stock);
}

int ft_print_normal(t_ls *stock)
{
	while (stock)
	{
		if((strcmp(stock->name,".")==0 || strcmp(stock->name,"..")==0 || (*stock->name) == '.' ))
		{
		}
		else 
			printf("%s\n", stock->name);
		stock = stock->next;
	}
	return (1);
}

void	ft_list_subfolders(char *name, t_ls *stock)
{
	char *dir;

	ft_print_normal(stock);

	while (stock)
	{
		if (S_ISDIR(stock->stat.st_mode) && (!(strcmp(stock->name,".") == 0 || strcmp(stock->name,"..") == 0 || (*stock->name) == '.' )))
		{
			dir = ft_strjoin(ft_strjoin(name, "/"), stock->name);
			ls(dir);
		}
		stock = stock->next;
	}
}

void	ls(char *name)
{
	t_ls *stock = NULL;
	stock = ft_store(name);
	ft_list_subfolders(name, stock);
}


int main()
{
	ls(".");
	return(0);
}
