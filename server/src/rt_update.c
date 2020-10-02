/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 17:37:22 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/20 17:38:42 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		ft_update__(t_sdls *app, t_rt *rt, t_vec vec_rot)
{
	if (app->flags.left)
	{
		vec_rot[0] -= 0.12;
		vec_rot = moves(vec_rot, rt->camera.orient);
		rt->camera.origin += vec_rot;
		app->flags.left = false;
	}
	if (app->flags.right)
	{
		vec_rot[0] += 0.12;
		vec_rot = moves(vec_rot, rt->camera.orient);
		rt->camera.origin += vec_rot;
		app->flags.right = false;
	}
}

static void		ft_update_(t_sdls *app, t_rt *rt)
{
	t_vec	vec_rot;

	vec_rot = (t_vec){0, 0, 0};
	if (app->flags.forward)
	{
		vec_rot[2] += 0.12;
		vec_rot = moves(vec_rot, rt->camera.orient);
		rt->camera.origin += vec_rot;
		app->flags.forward = false;
	}
	if (app->flags.backward)
	{
		vec_rot[2] -= 0.12;
		vec_rot = moves(vec_rot, rt->camera.orient);
		rt->camera.origin += vec_rot;
		app->flags.backward = false;
	}
	ft_update__(app, rt, vec_rot);
}

void			ft_update(t_sdls *app, t_rt *rt)
{
	if (app->flags.rot_x)
	{
		rt->camera.orient[0] += ROT_POWER;
		app->flags.rot_x = false;
	}
	if (app->flags.rot_x_min)
	{
		rt->camera.orient[0] -= ROT_POWER;
		app->flags.rot_x_min = false;
	}
	if (app->flags.rot_y)
	{
		rt->camera.orient[1] += ROT_POWER;
		app->flags.rot_y = false;
	}
	if (app->flags.rot_y_min)
	{
		rt->camera.orient[1] -= ROT_POWER;
		app->flags.rot_y_min = false;
	}
	app->flags.state_changed = 1;
	ft_update_(app, rt);
	cn_update(&(app->canvas));
}
