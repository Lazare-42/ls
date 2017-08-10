# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/26 20:03:26 by lazrossi          #+#    #+#              #
#    Updated: 2017/08/10 13:29:20 by lazrossi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

INCLUDES = includes/

SRC =srcs/ft_cmd_r.c srcs/ft_print_normal.c  srcs/ft_list_operations.c \
	 srcs/main.c srcs/ft_cmd_l.c srcs/ft_padding.c srcs/ft_print_info.c \
	 srcs/ft_find_path.c srcs/ft_place_element.c srcs/ft_store.c \
	 srcs/ft_print_errors.c srcs/ls.c  srcs/ft_cmd_g.c srcs/ft_parsing.c \
	 srcs/ft_cmd_ONE.c

OBJECT = $(notdir $(SRC:.c=.o)) 

CC = gcc -Wall -Wextra -Werror -g -I

CLEAN = /bin/rm -f

OK = echo "\033[32m OK ✓ \033[0m"

all: $(NAME)

$(NAME):
	@-make -C libft/ 
	@echo "Compiling $@ ..."
	@-$(CC) $(INCLUDES)  -c $(SRC)
	@-$(CC) $(INCLUDES) $(OBJECT) -L libft -lft -o $(NAME)
	@$(OK)

clean:
		@echo "Cleaning object files ..."
		@-make clean -C libft/
		@-$(CLEAN) $(OBJECT)
		@$(OK)

fclean: clean
		@echo "Deleting executables ..."
		@-make fclean -C libft/ 
		@-$(CLEAN) $(NAME)
		@$(OK)

re: fclean all
