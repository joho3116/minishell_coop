NAME	=	minishell

SRCS	= 	main.c \
			parse/parse.c \
			parse/parse_allocate_cmds.c \
			parse/parse_count_parse.c \
			parse/parse_only_alloc_space_for_cmds.c \
			parse/parse_only_redirection.c \
			parse/parse_only_redirection2.c \
			parse/lex.c \
			env/env.c \
			utils/find_node_at_idx_in_lst.c \
			utils/ft_perror.c \
			utils/print_error.c \
			utils/safe_free.c \
			utils/signal.c


LEAKS	=	-g3 -fsanitize=address
LIBFT	=	libft.a
LIBS	=	-L./libft -lft
HEADER	=	-I./includes
FLAG	= 	-Wall -Wextra -Werror
CC		=	gcc $(FLAG) -lreadline

OBJS = $(SRCS: .c=.o)

all		: $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME)	: $(LIBFT) $(OBJS)
	$(CC) $(LIBS) $(HEADER) -o $(NAME)

clean	:
	$(MAKE) -C ./libft clean
	$(RM) $(OBJS)

fclean	:
	$(MAKE) -C ./libs/libft fclean
	$(RM) $(NAME)

re		: fclean all
