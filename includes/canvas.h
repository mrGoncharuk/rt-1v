/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:22:57 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/20 18:27:03 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

# include "libui.h"

# define CN_WIDTH 800
# define CN_HEIGHT 800


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

typedef struct  	s_canvas
{
	t_window		wn;
	t_mousepos		mp;
    int				w;
	int				h;
	Uint32			draw_color;
	Uint32			*pixels;
	SDL_Texture		*field;
}					t_canvas;


void		cn_create_canvas(t_canvas *cn);
void		cn_event_handle(t_canvas *cn, SDL_Event *e, t_flags *f);
void		cn_update(t_canvas *cn);
void		cn_render(t_canvas *cn);
void		cn_destroy_canvas(t_canvas *canvas);
void		ft_draw_line(t_canvas *canv, t_vector2 p0, t_vector2 p1);
void		ft_pp_img(t_canvas *canv, int x, int y, Uint32 color);


#endif