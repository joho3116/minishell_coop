# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanlee <chanlee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/04 15:56:20 by chanlee           #+#    #+#              #
#    Updated: 2021/06/06 18:00:46 by chanlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -c -Wall -Wextra -Werror

NAME = libft.a

SRCS = ./ft_memset.c ./ft_bzero.c ./ft_memcpy.c\
		./ft_memccpy.c ./ft_memmove.c ./ft_memchr.c\
		./ft_memcmp.c ./ft_strlen.c ./ft_strlcpy.c\
		./ft_strlcat.c ./ft_strchr.c ./ft_strrchr.c\
		./ft_strnstr.c ./ft_strncmp.c ./ft_isdigit.c\
		./ft_isalpha.c ./ft_isalnum.c ./ft_isascii.c\
		./ft_isprint.c ./ft_toupper.c ./ft_tolower.c\
		./ft_atoi.c ./ft_calloc.c ./ft_strdup.c\
		./ft_substr.c ./ft_strjoin.c ./ft_strtrim.c\
		./ft_split.c ./ft_itoa.c ./ft_strmapi.c\
		./ft_putchar_fd.c ./ft_putstr_fd.c ./ft_putendl_fd.c\
		./ft_putnbr_fd.c\
		./ft_putnbr.c ./ft_putchar.c ./ft_putstr.c\
		./ft_lstnew.c ./ft_lstadd_front.c ./ft_lstsize.c\
		./ft_lstadd_back.c ./ft_lstdelone.c ./ft_lstclear.c\
		./ft_lstiter.c ./ft_lstmap.c ./ft_lstlast.c\
		./ft_strndup.c ./ft_isspace.c\
		./ft_strcmp.c\
		
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
	ar -cr $@ $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
