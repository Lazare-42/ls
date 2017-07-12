/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 17:14:32 by lazrossi          #+#    #+#             */
/*   Updated: 2017/07/12 08:44:21 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LS_H
# define LS_H

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/acl.h>
#include <stdlib.h>

#define CMD_l 1
#define CMD_R 2
#define CMD_a 4
#define CMD_r 8
#define CMD_t 16


typedef struct		s_ls
{
	char			*name;
	struct 			stat stat;
	struct 			s_ls *next;
}					t_ls;

void	ft_ls(char *foldername, int options);
void	ls(char *name, int options);
t_ls	*ft_store(char *foldername);
void	ft_print_normal(t_ls *stock);
int		ft_CMD_r(t_ls *stock, char *foldername);
void	ft_advance_stock_if_no_a(t_ls **stock);
void	ft_ls_reverse(t_ls **begin_list);
void	ft_free(t_ls **stock);
t_ls	*ft_place_elem(char *pathname, t_ls *stock, t_ls *new);
void	ft_time(t_ls *stock);
char	*find_path(char *name, const char *dirname);
#endif
