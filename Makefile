# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/15 19:28:21 by mhonchar          #+#    #+#              #
#    Updated: 2019/09/10 17:56:13 by mhonchar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1
LIBUI_NAME = libui.a
SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = includes/
LIBUI_DIR = libui/
FRM_DIR = frameworks

LIB = 	$(addprefix $(LIBUI_DIR), $(LIBUI_NAME)) 
		#-L./libsdl/lib -lSDL2 \
		-L./libsdl_image/lib -lSDL2_image \
		#-L./libsdl_ttf/lib -lSDL2_ttf 
		# -L./libsdl_mixer/lib -lSDL2_mixer

SRC_FILES =		main.c \
				sdl_init.c \
				sdl_clean.c \
				cn_canvas.c \
				cn_mainloop.c \
				draw_line.c \
				main_loop.c \
				bt_clear_canvas.c \
				rt_main.c \
				rt_color.c \
				rt_light.c \
				rt_sphere.c \
				rt_plane.c \
				rt_cylinder.c \
				rt_cone.c \
				rt_utils.c \
				rt_vec_op_utils.c \
				rt_parse.c \
				rt_clean.c \
				rt_rotation.c \
				pr_fields.c \
				pr_fields2.c \
				pr_lights.c \
				pr_objs.c \
				parson.c
				
HEADERS = 		$(INC_DIR)guimp.h \
				$(INC_DIR)canvas.h \
				$(LIBUI_DIR)includes/libui.h 

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

CC = gcc -g -fsanitize=address -flto -Ofast -pipe
CFLAGS = -Wall -Werror -Wextra
INC = 	-I $(INC_DIR) \
		-I libui/includes/ \
		-I libparson \
		-I $(CURDIR)/$(FRM_DIR)/SDL2.framework/⁨Versions⁩/A/Headers \
		-I $(CURDIR)/$(FRM_DIR)/SDL2_image.framework/Versions⁩/A/Headers \
		-F $(CURDIR)/$(FRM_DIR)


SDL_LNK	= -F $(CURDIR)/$(FRM_DIR) \
			-rpath $(CURDIR)/$(FRM_DIR) \
			-framework SDL2 -framework SDL2_image 


C_RED = \033[31m
C_GREEN = \033[32m
C_MAGENTA = \033[35m
C_NONE = \033[0m

all: $(NAME)

$(NAME): $(LIBUI_NAME) $(HEADERS) $(OBJ_DIR) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(INC) $(SDL_LNK) -o $(NAME)
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(LIBUI_NAME):
	@make -C $(LIBUI_DIR)

$(OBJ_DIR):
	@mkdir obj
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

clean:
	@rm -rf $(OBJ_DIR)*
	@make clean -C $(LIBUI_DIR)
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_RED)[done]$(C_NONE)\n" $@

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBUI_DIR)
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_RED)[done]$(C_NONE)\n" $@

re: fclean all

norm:
	@norminette $(SRC) $(HEADERS)
