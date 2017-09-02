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
./ft_print_info2.c \
./ft_print_normal.c \
./ft_store.c \
./ls.c \
./main.c \
./rotate.c 

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
OK = echo "[32m OK ✓ [0m"

all: lib mkbin $(NAME)

lib:
	@echo "Compiling libft ..."
	@-make -C $(LIBDIR)
	@$(OK)

mkbin:
	@mkdir -p $(ODIR)


$(NAME): $(OBJS)
	@echo "Compiling ft_ls ..."
	@-$(CC) $(CFLAGS) $(CDEBUG) -o $(NAME) $(OBJS) -I$(INCDIR) $(LDFLAGS) $(LNCURSES)
	@$(OK)

$(ODIR)/%.o : $(SDIR)/%.c
	$(CC) $(CFLAGS) $(CDEBUG) -c -o $@ $< -I$(INCDIR)

clean:
	@/bin/rm -rf $(ODIR)
	@make -C $(LIBDIR) clean

fclean: clean
	@/bin/rm -rf $(NAME)
	@make -C $(LIBDIR) fclean

re: fclean all
