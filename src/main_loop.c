/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 17:22:55 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/17 14:04:42 by mhonchar         ###   ########.fr       */
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
		if (SDL_KEYDOWN == event.type)
		{
			if (event.key.keysym.sym == SDLK_UP)
				app->flags.rot_y = true;
			if (event.key.keysym.sym == SDLK_DOWN)
				app->flags.rot_y_min = true;
			if (event.key.keysym.sym == SDLK_RIGHT)
				app->flags.rot_x = true;
			if (event.key.keysym.sym == SDLK_LEFT)
				app->flags.rot_x_min = true;
		}
	}
}

void	ft_update(t_sdls *app, t_rt *rt)
{
	rt_handle_rotation(app, rt);
	cn_update(&(app->canvas));
}

void	ft_render(t_sdls *app)
{
	cn_render(&(app->canvas));
}

void	ft_mainloop(t_sdls *app)
{
	t_rt rt;

	if (rt_parse_file(&rt, app->fname) == false)
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
	rt_clean(&rt);
}
