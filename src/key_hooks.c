/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 11:58:52 by khaniche          #+#    #+#             */
/*   Updated: 2019/09/20 17:03:39 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_event_(t_sdls *app)
{
	if (app->event.key.keysym.sym == SDLK_w)
		app->flags.forward = true;
	else if (app->event.key.keysym.sym == SDLK_s)
		app->flags.backward = true;
	else if (app->event.key.keysym.sym == SDLK_d)
		app->flags.right = true;
	else if (app->event.key.keysym.sym == SDLK_a)
		app->flags.left = true;
	else if (app->event.key.keysym.sym == SDLK_c)
		app->flags.clear = true;
	else if (app->event.key.keysym.sym == SDLK_p)
		app->flags.sepia = true;
	else if (app->event.key.keysym.sym == SDLK_o)
		app->flags.white = true;
	else if (app->event.key.keysym.sym == SDLK_i)
		app->flags.gray = true;
	else if (app->event.key.keysym.sym == SDLK_u)
		app->flags.cartoon = true;
	else if (app->event.key.keysym.sym == SDLK_y)
		app->flags.aliasing = true;
}

void	ft_event(t_sdls *app)
{
	while (SDL_PollEvent(&app->event))
	{
		if ((SDL_QUIT == app->event.type) || (SDL_KEYDOWN == app->event.type &&
			SDL_SCANCODE_ESCAPE == app->event.key.keysym.scancode))
			app->flags.running = false;
		if (SDL_KEYDOWN == app->event.type)
		{
			if (app->event.key.keysym.sym == SDLK_UP)
				app->flags.rot_y = true;
			if (app->event.key.keysym.sym == SDLK_LEFT)
				app->flags.rot_x_min = true;
			if (app->event.key.keysym.sym == SDLK_RIGHT)
				app->flags.rot_x = true;
			if (app->event.key.keysym.sym == SDLK_DOWN)
				app->flags.rot_y_min = true;
			ft_event_(app);
		}
	}
}
