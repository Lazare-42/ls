#include "ls.h"
#include "libft.h"
#include <sys/xattr.h>
#include <pwd.h>
#include <time.h>

t_ls	*ft_new_elem(char *name)
{
	t_ls	*tmp;
	if (!(tmp = malloc(sizeof(t_ls))))
		exit(1);
	tmp->name = ft_strdup(name);
	return (tmp);
}

t_ls	*ft_add_elem(char *name, t_ls *stock)
{
	t_ls *new;
	t_ls *check;

	new = ft_new_elem(name);
	if (!stock)
		return (new);
	check = stock;
	while (check && check->next && ft_strcmp(check->next->name, new->name) < 0)
		check = check->next;
	new->next = check->next;
	check->next = new;
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
		{
			stock = ft_add_elem(dent->d_name, stock);
			stat(stock->name, &(stock->stat));
		}
	}
	return (stock);
}
