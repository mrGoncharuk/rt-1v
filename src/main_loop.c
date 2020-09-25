/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 17:22:55 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/20 17:57:33 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_render(t_sdls *app)
{
	cn_render(&(app->canvas));
}

void	leaks_free(t_rt *rt)
{
	int	i;

	i = -1;
	while (++i < TEXTURES_COUNT)
		SDL_FreeSurface(rt->texture[i]);
	rt_clean(rt);
}

void	visual_effects(t_sdls *app)
{
	if (app->flags.sepia == true)
		sepia_image(app->canvas.pixels, app->canvas.pixels_copy);
	if (app->flags.white == true)
		white_rad(app->canvas.pixels, app->canvas.pixels_copy);
	if (app->flags.gray == true)
		gray_rad(app->canvas.pixels, app->canvas.pixels_copy);
	if (app->flags.cartoon == true)
		cartoon(app->canvas.pixels, app->canvas.pixels_copy);
	if (app->flags.aliasing == true)
		anti_aliasing(app->canvas.pixels_copy, 1);
	if (app->flags.clear == true)
	{
		app->flags.sepia = false;
		app->flags.white = false;
		app->flags.gray = false;
		app->flags.cartoon = false;
		app->flags.aliasing = false;
		app->flags.clear = false;
	}
}

void	ft_mainloop(t_sdls *app)
{
	t_rt	rt;

	if (!rt_parse_file(&rt, app->fname) || !load_textures(&rt))
		return ;
	check_light(&rt.lights);
	neg_obj(&rt.objs);
	rt.pixels = app->canvas.pixels;
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
		ft_memcpy(app->canvas.pixels_copy,
			app->canvas.pixels, CW * CH * sizeof(Uint32));
		visual_effects(app);
		ft_render(app);
		if (app->event.key.keysym.sym == SDLK_m)
			save_image("test.png", app->canvas.wn.renderer);
	}
	leaks_free(&rt);
}
