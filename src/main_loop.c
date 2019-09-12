/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 17:22:55 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/12 21:04:28 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_event(t_sdls *app)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if ((SDL_QUIT == event.type) || (SDL_KEYDOWN == event.type &&
			SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
			app->flags.running = false;
		if (SDL_KEYDOWN == event.type && event.key.keysym.sym == SDLK_UP)
		{
			app->flags.rot_x = true;
		}
		if (SDL_KEYDOWN == event.type && event.key.keysym.sym == SDLK_LEFT)
			app->flags.rot_y = true;
	}
}

void	ft_update(t_sdls *app, t_rt *rt)
{
	if (app->flags.rot_x)
	{
		rt->camera.orient[0] += ROT_POWER;
		app->flags.rot_x = false;
		app->flags.state_changed = 1;
	}
	if (app->flags.rot_y)
	{
		rt->camera.orient[1] += ROT_POWER;
		app->flags.rot_y = false;
		app->flags.state_changed = 1;
	}
	cn_update(&(app->canvas));
}

void	ft_render(t_sdls *app)
{
	cn_render(&(app->canvas));
}

void	ft_mainloop(t_sdls *app)
{
	t_rt rt;

	if (rt_parse_file(&rt, "scene.json") == false)
		return ;
	rt.pixels = (Uint32 *)malloc(CW * CH * sizeof(Uint32));
	while (app->flags.running)
	{
		ft_event(app);
		ft_update(app, &rt);
		if (app->flags.state_changed)
		{
			rt_thread_tracer(&rt);
			app->canvas.pixels = rt.pixels;
			app->flags.state_changed = 0;
		}
		ft_render(app);
	}
}
