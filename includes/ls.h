/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 17:14:32 by lazrossi          #+#    #+#             */
/*   Updated: 2017/08/11 15:48:43 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include "../libft/libft.h"
# include <string.h>
# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/xattr.h>

# define CMD_L 1
# define CMD_R 2
# define CMD_A 4
# define CMD_REVERSE 8
# define CMD_T 16
# define CMD_LAST_ACCESS 32
# define CMD_G 64
# define CMD_S 128
# define CMD_U 256
# define CMD_1 512

typedef struct		s_ls
{
	char			*name;
	struct stat		stat;
	struct s_ls		*right;
	struct s_ls		*left;
}					t_ls;

void				ft_ls(char *foldername, int options);
void				ls(char *name, int options, int file_mode);
t_ls				*ft_store(char *foldername, DIR *dir, int sort_options);
void				ft_print_normal(t_ls *stock);
void				ft_print_usage_error(char error);
void				ft_print_name(char *name, int st_mode);
t_ls				*ft_advance_stock_if_no_a(t_ls *stock);
void				ft_cmd_reverse(t_ls **begin_list);
void				ft_cmd_1(t_ls *stock);
void				ft_cmd_t(t_ls **stock);
int					ft_cmd_l(t_ls *stock, char *foldername, int file_mode);
int					ft_cmd_g(t_ls *stock, char *foldername, int file_mode);
void				ft_cmd_r(t_ls *stock, char *name, int options);
void				ft_free(t_ls **stock);
t_ls				*ft_place_elem(t_ls *stock, t_ls *new, int sort_options);
void				ft_time(t_ls *stock);
int					*ft_max_size(t_ls *stock, int file_mode);
void				ft_put_whites(int max_str_len, int fillup, int options);
void				ft_print_errors(char *name);
void				ft_print_time(t_ls *tmp, time_t local_time);
char				*find_path(char *name, char *foldername);
char				ft_mode(int mode);
void				ft_print_rights(t_ls *stock, char *path);
void				ft_print_grp_usr(t_ls *stock, int *max_size);
void				print_lnkabout(char *fpath);
int					ft_check_usage(char ***av);
int					ft_check_file_errors(char *folder);
int					ft_stock_commands(char command, int command_options);
void				ft_print_grp_usr(t_ls *stock, int *max_size);
void				print_lnkabout(char *fpath);
void				ft_print_rights(t_ls *stock, char *path);

#endif
