/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 17:39:32 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/11 18:36:08 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "SDL2/SDL.h"
# include <stdbool.h>
# include "error_handler.h"

typedef struct		s_window
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	Uint32			id;
	int				w;
	int				h;
	bool			mouse_focus;
	bool			keyboard_focus;
	bool			full_screen;
	bool			minimized;
	bool			shown;
}					t_window;

void				wn_create(t_window *wn);
bool				wn_init(t_window *wn, const char *title, SDL_Rect clip_rect,
						Uint32 flags);
SDL_Renderer		*wn_create_renderer(t_window *wn);
void				wn_handle_event(t_window *wn, SDL_Event *e);
void				wn_destroy(t_window *wn);

#endif
