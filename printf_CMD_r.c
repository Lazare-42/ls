/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_CMD_r.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 03:22:16 by lazrossi          #+#    #+#             */
/*   Updated: 2017/07/04 03:26:16 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <sys/xattr.h>
#include "ls.h"
#include "libft.h"
#include <pwd.h>
#include <time.h>

int		ft_CMD_r(t_ls *stock)
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
			ft_putchar( S_ISDIR(stock->stat.st_mode) ? 'd' : '-');
			ft_putchar( (stock->stat.st_mode & S_IRUSR) ? 'r' : '-');
			ft_putchar( (stock->stat.st_mode & S_IWUSR) ? 'w' : '-');
			ft_putchar( (stock->stat.st_mode & S_IXUSR) ? 'x' : '-');
			ft_putchar( (stock->stat.st_mode & S_IRGRP) ? 'r' : '-');
			ft_putchar( (stock->stat.st_mode & S_IWGRP) ? 'w' : '-');
			ft_putchar( (stock->stat.st_mode & S_IXGRP) ? 'x' : '-');
			ft_putchar( (stock->stat.st_mode & S_IROTH) ? 'r' : '-');
			if (listxattr(stock->name, NULL, stock->stat.st_size, XATTR_SHOWCOMPRESSION))
			{
				i = 1;
				ft_putchar('@');
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
