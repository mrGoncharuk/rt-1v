/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 17:39:11 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/21 17:21:15 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void		wn_create(t_window *wn)
{
	wn->win = NULL;
	wn->mouse_focus = false;
	wn->keyboard_focus = false;
	wn->full_screen = false;
	wn->minimized = false;
	wn->w = 0;
	wn->h = 0;
}

bool		wn_init(t_window *wn, const char *title, SDL_Rect clip_rect, Uint32 flags)
{
	wn_create(wn);
	if (!flags)
		flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	wn->win = SDL_CreateWindow(title, clip_rect.x, clip_rect.y, clip_rect.w, clip_rect.h, flags);
	if (wn->win != NULL)
	{
		wn->mouse_focus = true;
		wn->keyboard_focus = true;
		wn->w = clip_rect.w;
		wn->h = clip_rect.h;
		wn->renderer = SDL_CreateRenderer(wn->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (wn->renderer == NULL)
		{
			SDL_DestroyWindow(wn->win);
			wn->win = NULL;
			err_sdl(ERR_RENDERER_CREATE);
		}
		else
		{
			//SDL_SetRenderDrawColor(wn->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			wn->id = SDL_GetWindowID(wn->win);
			wn->shown = true;
		}
	}
	else
		err_sdl(ERR_WIN_CREATE);
	return ((wn->win != NULL) && (wn->renderer != NULL));
}

void			wn_handle_event(t_window *wn, SDL_Event *e)
{
	bool	update_caption;

	if (e->type == SDL_WINDOWEVENT)
	{
		update_caption = false;
		if (e->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		{
			wn->w = e->window.data1;
			wn->h = e->window.data2;
		}
		else if (e->window.event == SDL_WINDOWEVENT_EXPOSED)
			SDL_RenderPresent(wn->renderer);
		else if (e->window.event == SDL_WINDOWEVENT_ENTER)
		{
			wn->mouse_focus = true;
			update_caption = true;
		}
		else if (e->window.event == SDL_WINDOWEVENT_LEAVE)
		{
			wn->mouse_focus = false;
			update_caption = true;
		}
		else if (e->window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
		{
			wn->mouse_focus = true;
			update_caption = true;
		}
		else if (e->window.event == SDL_WINDOWEVENT_FOCUS_LOST)
		{
			wn->mouse_focus = false;
			update_caption = true;
		}
		else if (e->window.event == SDL_WINDOWEVENT_MINIMIZED)
			wn->minimized = true;
		else if (e->window.event == SDL_WINDOWEVENT_MAXIMIZED)
			wn->minimized = false;
		else if (e->window.event == SDL_WINDOWEVENT_RESTORED)
			wn->minimized = false;
	}
}

void			wn_destroy(t_window *wn)
{
	SDL_DestroyRenderer(wn->renderer);
	SDL_DestroyWindow(wn->win);
}

