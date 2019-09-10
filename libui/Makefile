# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/24 18:09:23 by mhonchar          #+#    #+#              #
#    Updated: 2019/09/10 17:32:42 by mhonchar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libui.a

LIBFT_DIR = libft/

LIBFT = libft.a
FRM_DIR = frameworks
#################################################
SRC_DIR = src/

SRC_FILES =	error_handler.c \
				window.c \
				button.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

#################################################
INC_DIR = includes/

HEADERS =	libui.h \
			error_handler.h \
			button.h \
			window.h


INCLUDES = $(addprefix $(INC_DIR), $(HEADERS))

INC =	-I $(INC_DIR) \
		-I $(LIBFT_DIR) \
		-I $(FRM_DIR)/SDL2.framework/Versions/A/Headers \
		-I $(FRM_DIR)/SDL2_image.framework/Versions/A/Headers \
		-F $(FRM_DIR)

#################################################
OBJ_DIR = obj/

OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

OBJ_FT = libft/*.o
#################################################
FLAGS = -Wall -Werror -Wextra -c


SDL_INC	= 



CC = gcc

C_RED = \033[31m
C_GREEN = \033[32m
C_MAGENTA = \033[35m
C_NONE = \033[0m

all: $(NAME)


$(NAME): $(LIBFT_DIR) $(INCLUDES) $(OBJ_DIR) $(OBJ)
	@make -C $(LIBFT_DIR) 
	@ar rc $(NAME) $(OBJ) $(OBJ_FT) 

$(OBJ_DIR):
	@mkdir obj
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDES)
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

clean:
	@rm -rf $(OBJ_DIR)*
	@make fclean -C $(LIBFT_DIR)
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_RED)[done]$(C_NONE)\n" $@

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_RED)[done]$(C_NONE)\n" $@

re: fclean all

norm:
	@norminette $(SRC) $(HEADERS)
