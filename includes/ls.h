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

#include "../libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/acl.h>
#include <stdlib.h>
#include <errno.h>

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
void	ls(char *name, int options, int file_mode);
t_ls	*ft_store(char *foldername, DIR *dir, int options);
void	ft_print_normal(t_ls *stock);
void	ft_print_usage_error(char error);
t_ls	*ft_advance_stock_if_no_a(t_ls *stock);
void	ft_CMD_r(t_ls **begin_list);
void	ft_CMD_t(t_ls **stock);
int		ft_CMD_l(t_ls *stock, char *foldername, int file_mode);
void	ft_CMD_R(t_ls *stock, char *name, int options);
void	ft_free(t_ls **stock);
t_ls	*ft_place_elem(t_ls *stock, t_ls *new, int time);
void	ft_time(t_ls *stock);
int		*ft_max_size(t_ls *stock, int file_mode);
void	ft_put_whites(int max_str_len, int fillup, int options);
void	ft_print_errors(char *name);
void	ft_print_time(t_ls *tmp, time_t local_time);
char	*find_path(char *name, char *foldername);

#endif
