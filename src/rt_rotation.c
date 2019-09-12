/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rotation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 19:51:00 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/12 18:43:07 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	rt_rotate_camera(t_camera *camera, t_vec ray_dir)
{
	t_vec	res;
	double	tmp;

	tmp = ray_dir[1];
	res[0] = ray_dir[0];
	res[1] = tmp * cos(camera->orient[0]) + ray_dir[2] *
				sin(camera->orient[0]);
	res[2] = -tmp * sin(camera->orient[0]) + ray_dir[2] *
				cos(camera->orient[0]);
	return (res);
}
