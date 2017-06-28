/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 19:08:21 by lazrossi          #+#    #+#             */
/*   Updated: 2017/06/28 16:40:37 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/xattr.h>
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
	char *time;
	acl_t acl;
	int i;
	static int k = 0;

	while (stock && stock->next)
	{
		if((strcmp(stock->name,".")==0 || strcmp(stock->name,"..")==0 || (*stock->name) == '.' ))
		{
		}
		else 
		{
			printf( S_ISDIR(stock->stat.st_mode) ? "d" : "-");
			printf( (stock->stat.st_mode & S_IRUSR) ? "r" : "-");
			printf( (stock->stat.st_mode & S_IWUSR) ? "w" : "-");
			printf( (stock->stat.st_mode & S_IXUSR) ? "x" : "-");
			printf( (stock->stat.st_mode & S_IRGRP) ? "r" : "-");
			printf( (stock->stat.st_mode & S_IWGRP) ? "w" : "-");
			printf( (stock->stat.st_mode & S_IXGRP) ? "x" : "-");
			printf( (stock->stat.st_mode & S_IROTH) ? "r" : "-");
			printf( (stock->stat.st_mode & S_IWOTH) ? "w" : "-");
			printf( (stock->stat.st_mode & S_IXOTH) ? "x" : "-");
			if (listxattr(stock->name, NULL, stock->stat.st_size, XATTR_SHOWCOMPRESSION))
			{
				i = 1;
				printf("%s", "@");
			}
			acl = acl_get_file(stock->name, ACL_TYPE_EXTENDED);
			if (acl)
			{
				printf("%s", "+");
				i = 1;
			}
			if (!(i))
				printf("%s", " ");
			printf("   %d", stock->stat.st_nlink);
			printf(" %s", getpwuid(stock->stat.st_uid)->pw_name);
			printf("   %lld", stock->stat.st_size);
			k = k + stock->stat.st_blocks;
			time = ft_strsub(ctime(&(stock->stat.st_mtime)), 4, 12);
			printf("   %s ", time);
			printf("%s\n", stock->name);

		}
		stock = stock->next;
	}
	k = k / 512;
	printf("%d\n", k);
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
