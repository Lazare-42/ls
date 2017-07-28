# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/26 20:03:26 by lazrossi          #+#    #+#              #
#    Updated: 2017/07/26 20:20:52 by lazrossi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

INCLUDES = includes/

SRC = srcs/ft_CMD_r.c srcs/main.c srcs/ft_free.c srcs/ft_list_reverse.c srcs/ft_place_element.c srcs/ft_print_normal.c srcs/ft_store.c srcs/ls.c srcs/main.c srcs/ft_CMD_l.c srcs/ft_padding.c srcs/ft_print_normal.c

OBJECT = *.o 

all: $(NAME)

$(NAME):
	make -C libft/ 
	gcc -Wall -Wextra -Werror -g  -I $(INCLUDES)  -c $(SRC)
	gcc -Wall -Wextra -Werror -I $(INCLUDES) $(OBJECT) -L libft -lft -o $(NAME)

clean:
		make clean -C libft/
		/bin/rm -f $(OBJECT)

fclean: clean
		make fclean -C libft/ 
		/bin/rm -f $(NAME)

re: fclean all
