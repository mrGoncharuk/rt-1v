/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:53:10 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/13 16:54:47 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_handle_rotation(t_sdls *app, t_rt *rt)
{
	if (app->flags.rot_x)
	{
		rt->camera.orient[0] += ROT_POWER;
		app->flags.rot_x = false;
		app->flags.state_changed = 1;
	}
	if (app->flags.rot_x_min)
	{
		rt->camera.orient[0] -= ROT_POWER;
		app->flags.rot_x_min = false;
		app->flags.state_changed = 1;
	}
	if (app->flags.rot_y)
	{
		rt->camera.orient[1] += ROT_POWER;
		app->flags.rot_y = false;
		app->flags.state_changed = 1;
	}
	if (app->flags.rot_y_min)
	{
		rt->camera.orient[1] -= ROT_POWER;
		app->flags.rot_y_min = false;
		app->flags.state_changed = 1;
	}
}
