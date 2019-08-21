/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 14:49:59 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/14 16:17:53 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUTTON_H
# define BUTTON_H

# include "libui.h"
# define TOTAL_BUTTONS 1
# define STD_BUTTON_SIZE 32
# define STD_BT_LABLE_SIZE 16

typedef struct		s_flags t_flags;

enum					e_bt_sprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_DOWN = 1,
    BUTTON_SPRITE_TOTAL = 2
};

typedef struct			s_lbutton
{
	SDL_Rect			clip_rect;
	SDL_Texture			*sprite[BUTTON_SPRITE_TOTAL];
	char				*label;
	int					id;
	void				(*handle_event)(SDL_Event *event, struct s_lbutton *bt, t_flags *flags);
	bool				is_active;
	enum e_bt_sprite	curr_sprite;
}						t_lbutton;

void					bt_create(t_lbutton *bt, SDL_Rect r, const char *label, void (*handle_event)(SDL_Event *, t_lbutton *, t_flags *));
void					bt_load_sprites(t_lbutton *bt, const char *bt_out, const char *bt_down, SDL_Renderer *renderer);
void					bt_render(t_lbutton *bt, SDL_Renderer *renderer);
void					bt_destroy(t_lbutton *bt);

#endif