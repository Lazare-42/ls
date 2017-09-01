NAME = ft_ls

SOURCES = ./ft_CMD_g.c \
./ft_CMD_l.c \
./ft_cmd_one.c \
./ft_CMD_R.c \
./ft_find_path.c \
./ft_list_operations.c \
./ft_padding.c \
./ft_parsing.c \
./ft_place_element.c \
./ft_print_errors.c \
./ft_print_info.c \
./ft_print_normal.c \
./ft_store.c \
./ls.c \
./main.c 

LIBDIR = libft
SDIR = srcs
ODIR = bin
CFLAGS = -Wall -Wextra -Werror
CDEBUG = -fno-omit-frame-pointer -fsanitize=address -g
INCDIR = includes
LDFLAGS = -L$(LIBDIR) -lft
LNCURSES = -lncurses
CC = clang
SRCS = $(addprefix $(SDIR)/, $(SOURCES:.c=.c))
OBJS = $(addprefix $(ODIR)/, $(SOURCES:.c=.o))
OK = echo 033[32m OK ✓ 033[0m

all: lib mkbin $(NAME)

lib:
	make -C $(LIBDIR)

mkbin:
	@mkdir -p $(ODIR)


$(NAME): $(OBJS)
	@echo "Compiling ft_ls ..."
	@-$(CC) $(CFLAGS) $(CDEBUG) -o $(NAME) $(OBJS) -I$(INCDIR) $(LDFLAGS) $(LNCURSES)
	@$(OK) Makefile

$(ODIR)/%.o : $(SDIR)/%.c
	$(CC) $(CFLAGS) $(CDEBUG) -c -o $@ $< -I$(INCDIR)

clean:
	@/bin/rm -rf $(ODIR)
	@make -C $(LIBDIR) clean

fclean: clean
	@/bin/rm -rf $(NAME)
	@make -C $(LIBDIR) fclean

re: fclean all
