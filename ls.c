/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 19:08:21 by lazrossi          #+#    #+#             */
/*   Updated: 2017/06/26 15:20:10 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft.h"
#include <pwd.h>
#include <time.h>
int ft_print_normal(t_ls *stock);
void	ls(char *name);

t_ls	*ft_store(char *foldername)
{
	t_ls	*stock = NULL;
	DIR *dir;
	struct dirent *dent;
	dir = opendir(foldername);
	t_ls *tmp;

	printf ("voici le nom du dossier envoye a ft_store : %s\n", foldername);
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
	char time[13];
	int i;
	int k;
	i = 0;
	k = 4;

	while (stock)
	{
		if((strcmp(stock->name,".")==0 || strcmp(stock->name,"..")==0 || (*stock->name) == '.' ))
		{
		}
		else 
		{
			printf("%s", stock->name);
			printf("   %s", getpwuid(stock->stat.st_uid)->pw_name);
			printf("   %lld", stock->stat.st_size);
			while (i < 12) 
			{
				time[i] = ctime(&(stock->stat.st_atimespec.tv_sec))[k];
				i++;
				k++;
			}
			printf("   %s\n", time);

		}
		stock = stock->next;
	}
	return (1);
}

int		ft_list_subfolders(char *name, t_ls *stock)
{
	char *dir;


	while (stock)
	{
		if (S_ISDIR(stock->stat.st_mode) && (!(strcmp(stock->name,".") == 0 || strcmp(stock->name,"..") == 0 || (*stock->name) == '.' )))
		{
			dir = ft_strjoin(ft_strjoin(name, "/"), (stock->name));
			ls(dir);
			return (1);
		}
		stock = stock->next;
	}
	return (0);
}

void	ls(char *name)
{
	t_ls *stock = NULL;
	stock = ft_store(name);
	//ft_list_subfolders(name, stock);
}


int main()
{
	ls(".");
	return(0);
}
