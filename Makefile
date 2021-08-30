NAME	=	minishell

SRCS	= 	main/main.c \
			parse/parse.c \
			parse/lex.c \


LEAKS	=	-g3 -fsanitize=address

LIBFT	=	libft.a

LIBS	=	-L./libft -lft

HEADER	=	-I./includes

FLAG	= 	-Wall -Wextra -Werror

CC		=	gcc

RM		=	rm -rf

all		: $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME)	: $(LIBFT)
	$(CC) $(SRCS) $(LIBS) $(HEADER) $(FLAG) -o $(NAME)

clean	:
	$(MAKE) -C ./libs/libft clean
	rm -rf $(OBJS)

fclean	:
	$(MAKE) -C ./libs/libft fclean
	rm -rf $(NAME)

re		: fclean all
