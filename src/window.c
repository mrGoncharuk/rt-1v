/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaniche <khaniche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 17:39:11 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/17 11:24:55 by khaniche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void	wn_create(t_window *wn)
{
	wn->win = NULL;
	wn->mouse_focus = false;
	wn->keyboard_focus = false;
	wn->full_screen = false;
	wn->minimized = false;
	wn->w = 0;
	wn->h = 0;
}

bool	wn_init(t_window *wn, const char *title, SDL_Rect c_r, Uint32 flags)
{
	wn_create(wn);
	if (!flags)
		flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	wn->win = SDL_CreateWindow(title, c_r.x, c_r.y, c_r.w, c_r.h, flags);
	if (wn->win != NULL)
	{
		wn->mouse_focus = true;
		wn->keyboard_focus = true;
		wn->w = c_r.w;
		wn->h = c_r.h;
		wn->renderer = SDL_CreateRenderer(wn->win, -1,
						SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (wn->renderer == NULL)
		{
			SDL_DestroyWindow(wn->win);
			wn->win = NULL;
			err_sdl(ERR_RENDERER_CREATE);
			return (false);
		}
		wn->id = SDL_GetWindowID(wn->win);
		wn->shown = true;
	}
	else
		err_sdl(ERR_WIN_CREATE);
	return ((wn->win != NULL) && (wn->renderer != NULL));
}

void	wn_destroy(t_window *wn)
{
	SDL_DestroyRenderer(wn->renderer);
	SDL_DestroyWindow(wn->win);
}
