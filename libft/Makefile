# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/24 18:09:23 by mhonchar          #+#    #+#              #
#    Updated: 2019/09/11 18:41:16 by mhonchar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = 	ft_atoi.c\
		ft_lstdelone.c\
		ft_memmove.c\
		ft_memdel.c\
		ft_strcat.c\
		ft_strjoin.c\
		ft_strnstr.c\
		ft_bzero.c\
		ft_lstiter.c\
		ft_memset.c\
		ft_strchr.c\
		ft_strlcat.c\
		ft_strrchr.c\
		ft_isalnum.c\
		ft_lstmap.c\
		ft_putchar.c\
		ft_strclr.c\
		ft_strlen.c\
		ft_strsplit.c\
		ft_isalpha.c\
		ft_lstnew.c\
		ft_putchar_fd.c\
		ft_strcmp.c\
		ft_strmap.c\
		ft_strstr.c\
		ft_isascii.c\
		ft_memalloc.c\
		ft_putendl.c\
		ft_strcpy.c\
		ft_strmapi.c\
		ft_strsub.c\
		ft_isdigit.c\
		ft_memccpy.c\
		ft_putendl_fd.c\
		ft_strdel.c\
		ft_strncat.c\
		ft_strtrim.c\
		ft_isprint.c\
		ft_memchr.c\
		ft_putnbr.c\
		ft_strdup.c\
		ft_strncmp.c\
		ft_tolower.c\
		ft_itoa.c\
		ft_memcmp.c\
		ft_putnbr_fd.c\
		ft_strequ.c\
		ft_strncpy.c\
		ft_toupper.c\
		ft_lstadd.c\
		ft_memcpy.c\
		ft_putstr.c\
		ft_striter.c\
		ft_strnequ.c\
		ft_lstdel.c\
		ft_putstr_fd.c\
		ft_striteri.c\
		ft_strnew.c\
		ft_iswhitespace.c\
		ft_abs.c\
		ft_factorial.c\
		ft_pow.c\
		ft_sqrt.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Werror -Wextra

OPT = -c

all: $(NAME)

$(NAME):
	@gcc $(FLAGS) $(OPT) $(SRCS)
	@ar rc $(NAME) $(OBJS)

clean:
	@/bin/rm -f $(OBJS)

fclean: clean
	@/bin/rm -f $(NAME)

re:	fclean all
