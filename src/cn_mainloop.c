/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_mainloop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 19:36:54 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/12 15:25:38 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cn_event_handle(t_canvas *cn, SDL_Event *e, t_flags *f)
{
	if (e->type == SDL_MOUSEBUTTONUP)
		if (e->button.button == SDL_BUTTON_LEFT)
			f->lmb_down = false;
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		if (e->button.button == SDL_BUTTON_LEFT)
		{
			SDL_GetMouseState(&(cn->mp.lmb_down.x), &(cn->mp.lmb_down.y));
			cn->mp.motion = cn->mp.lmb_down;
			cn->mp.temp = cn->mp.lmb_down;
			f->lmb_down = true;
		}
	}
	if (e->type == SDL_MOUSEMOTION)
	{
		if (f->lmb_down)
		{
			cn->mp.motion.x = e->motion.x;
			cn->mp.motion.y = e->motion.y;
		}
	}
}

void		cn_update(t_canvas *cn)
{
	SDL_UpdateTexture(cn->field, NULL, cn->pixels, cn->w * sizeof(Uint32));
}

void		cn_render(t_canvas *cn)
{
	SDL_RenderClear(cn->wn.renderer);
	SDL_RenderCopy(cn->wn.renderer, cn->field, NULL, NULL);
	SDL_RenderPresent(cn->wn.renderer);
}
