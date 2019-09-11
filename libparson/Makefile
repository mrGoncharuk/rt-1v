# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/11 18:39:31 by mhonchar          #+#    #+#              #
#    Updated: 2019/09/11 18:45:57 by mhonchar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = parson.c
OBJS = $(SRC:.c=.o)
NAME = libparson.a
all: $(NAME)

$(NAME):
	@gcc -Wall -Werror -Wextra  -c $(SRC)
	@ar rc $(NAME) $(OBJS)

clean:
	@/bin/rm -f $(OBJS)

fclean: clean
	@/bin/rm -f $(NAME)

re:	fclean all