/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:22:57 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/12 20:09:27 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H
# define CN_WIDTH 800
# define CN_HEIGHT 800
# include "SDL2/SDL.h"
# include "window.h"
# include "error_handler.h"
# define STD_WIDTH 800
# define STD_HEIGHT 600

typedef struct s_flags	t_flags;

typedef struct		s_vector2
{
	int				x;
	int				y;
}					t_vector2;

typedef struct		s_mousepos
{
	t_vector2		lmb_down;
	t_vector2		motion;
	t_vector2		temp;
}					t_mousepos;

typedef struct		s_canvas
{
	t_window		wn;
	t_mousepos		mp;
	int				w;
	int				h;
	Uint32			draw_color;
	Uint32			*pixels;
	SDL_Texture		*field;
}					t_canvas;

void				cn_create_canvas(t_canvas *cn);
void				cn_event_handle(t_canvas *cn, SDL_Event *e, t_flags *f);
void				cn_update(t_canvas *cn);
void				cn_render(t_canvas *cn);
void				cn_destroy_canvas(t_canvas *canvas);
void				ft_pp_img(Uint32 *pixels, int x, int y, Uint32 color);

#endif
