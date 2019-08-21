/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_clear_canvas.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 19:47:04 by mhonchar          #+#    #+#             */
/*   Updated: 2019/07/25 20:25:36 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

void		bt_event_clear_canvas(SDL_Event *e, t_lbutton *bt, t_flags *flags)
{
	int		x;
	int		y;
	bool inside;

	inside = true;
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        SDL_GetMouseState( &x, &y );
        if( x < bt->clip_rect.x )
            inside = false;
        else if( x > bt->clip_rect.x + bt->clip_rect.w )
            inside = false;
        else if( y < bt->clip_rect.y )
            inside = false;
        else if( y > bt->clip_rect.y + bt->clip_rect.h )
            inside = false;
        if( !inside )
            bt->curr_sprite = BUTTON_SPRITE_MOUSE_OUT;
        else
        {
            if (e->type == SDL_MOUSEBUTTONDOWN)
            {
				bt->curr_sprite = BUTTON_SPRITE_MOUSE_DOWN;
				flags->clear_canvas = true;
            }
            if (e->type == SDL_MOUSEBUTTONUP)
            {
				bt->curr_sprite = BUTTON_SPRITE_MOUSE_OUT;
				flags->clear_canvas = true;
            }
        }
    }
}

void		bt_clear_canvas(t_canvas *canvas, t_flags *flags)
{
	ft_memset(canvas->pixels, 255, canvas->h * canvas->w * sizeof(Uint32));
	flags->clear_canvas = false;
}
