/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 15:21:23 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/26 17:44:12 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec		rt_canvas_to_viewport(int x, int y)
{
	return ((t_vec){(double)x * (double)VIEWPORT_WIDTH / (double)CW,
				(double)y * (double)VIEWPORT_HEIGHT / (double)CH, DIST_CAM_PP});
}

t_channel	rt_enlightenment(t_channel color, double intensity)
{
	if ((color.r = color.r * intensity) > 255)
		color.r = 255;
	if ((color.g = color.g * intensity) > 255)
		color.g = 255;
	if ((color.b = color.b * intensity) > 255)
		color.b = 255;
	return (color);
}

t_vec		rt_reflect_ray(t_vec normal, t_vec ray_dir)
{
	return (2 * normal * dot(normal, ray_dir) - ray_dir);
}
