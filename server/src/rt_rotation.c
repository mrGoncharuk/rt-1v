/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rotation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 19:51:00 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/20 17:37:46 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_vec	rt_rotate_camera_x(t_camera *camera, t_vec ray_dir)
{
	double	tmp;

	tmp = ray_dir[0];
	ray_dir[0] = tmp * cos(camera->orient[0]) + ray_dir[2] *
				sin(camera->orient[0]);
	ray_dir[2] = -tmp * sin(camera->orient[0]) + ray_dir[2] *
				cos(camera->orient[0]);
	return (ray_dir);
}

static t_vec	rt_rotate_camera_y(t_camera *camera, t_vec ray_dir)
{
	double	tmp;

	tmp = ray_dir[1];
	ray_dir[1] = tmp * cos(camera->orient[1]) + ray_dir[2] *
				sin(camera->orient[1]);
	ray_dir[2] = -tmp * sin(camera->orient[1]) + ray_dir[2] *
				cos(camera->orient[1]);
	return (ray_dir);
}

t_vec			rt_rotate_camera(t_camera *camera, t_vec ray_dir)
{
	ray_dir = rt_rotate_camera_x(camera, ray_dir);
	ray_dir = rt_rotate_camera_y(camera, ray_dir);
	return (ray_dir);
}
