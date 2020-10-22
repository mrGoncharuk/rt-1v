# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/15 19:28:21 by mhonchar          #+#    #+#              #
#    Updated: 2019/09/20 17:38:30 by mhonchar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
LIBFT_NAME = libft.a
LIBPARSON_NAME = libparson.a
SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = includes/
FRM_DIR = frameworks
LIBFT_DIR = libft/
LIBPARSON_DIR = libparson/
LIB = 	$(addprefix $(LIBFT_DIR), $(LIBFT_NAME)) \
		$(addprefix $(LIBPARSON_DIR), $(LIBPARSON_NAME)) 


SRC_FILES =		cn_mainloop.c \
				key_hooks.c \
				pr_fields2.c \
				pr_objs.c \
				rt_cone.c \
				rt_light.c \
				rt_plane.c \
				rt_tx_texture.c \
				sdl_clean.c \
				anti_aliasing.c \
				color_disruptions.c \
				color_disruptions_.c \
				main.c \
				pr_fields3.c \
				rt_clean.c \
				rt_cut_and_sort_roots.c \
				rt_main.c \
				rt_rotation.c \
				rt_utils.c \
				rt_utils_.c \
				sdl_init.c \
				cam_matrix_rotation.c \
				draw_line.c \
				main_loop.c \
				pr_fields4.c \
				rt_color.c \
				rt_cylinder.c \
				rt_parabaloid.c \
				rt_sphere.c \
				rt_vec_op_utils.c \
				window.c \
				cn_canvas.c \
				er_error_handler.c \
				pr_fields.c \
				pr_lights.c \
				rt_compose_obj.c \
				rt_figure_defenetion.c \
				rt_parse.c \
				rt_threader.c \
				rt_visual_effects.c \
				rt_shadows.c \
				rt_update.c \
				rt_server.c \
				handle_events.c
				
HEADERS = 		$(INC_DIR)canvas.h \
				$(INC_DIR)error_handler.h \
				$(INC_DIR)window.h \
				$(LIBFT_DIR)/libft.h 

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))



CC = clang -g
CFLAGS = -Wall -Werror -Wextra
#  -flto -Ofast -pipe
INC = 	-I $(INC_DIR) \
		-I libft \
		-I libparson \


LIBS_LINK = -l SDL2 \
			-l SDL2_image \
			-lm \
			-lpthread


C_RED = \033[31m
C_GREEN = \033[32m
C_MAGENTA = \033[35m
C_NONE = \033[0m

all: $(NAME)

$(NAME): $(LIBFT_NAME) $(LIBPARSON_NAME) $(HEADERS) $(OBJ_DIR) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(INC) $(LIBS_LINK) -o $(NAME)
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(LIBFT_NAME):
	@make -C $(LIBFT_DIR)

$(LIBPARSON_NAME):
	@make -C $(LIBPARSON_DIR)

$(OBJ_DIR):
	@mkdir obj
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

clean:
	@rm -rf $(OBJ_DIR)*
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(LIBPARSON_DIR)
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_RED)[done]$(C_NONE)\n" $@

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(LIBPARSON_DIR)
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_RED)[done]$(C_NONE)\n" $@

re: fclean all

norm:
	@norminette $(SRC) $(HEADERS)
