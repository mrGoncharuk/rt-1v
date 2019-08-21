/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guimp.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 17:36:27 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/19 18:38:55 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUIMP_H
# define GUIMP_H

# include <stdbool.h>
# include <unistd.h>
# include "libui.h"
# include "canvas.h"
# include "toolbox.h"
# include "SDL.h"
# define STD_WIDTH 800
# define STD_HEIGHT 600

typedef struct		s_flags
{
	bool			running;
	bool			lmb_down;
	bool			clear_canvas;
}					t_flags;

typedef struct		s_sdls
{
	t_canvas		canvas;
	t_toolbox		toolbox;
	t_flags			flags;
}					t_sdls;

void				ft_sdl_init(t_sdls *app);
void				ft_sdl_clean(t_sdls *app);
void				ft_mainloop(t_sdls *app);
void				bt_clear_canvas(t_canvas *canvas, t_flags *flags);
void				bt_event_clear_canvas(SDL_Event *e, t_lbutton *bt, t_flags *flags);
#endif
