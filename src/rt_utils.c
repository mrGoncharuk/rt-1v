/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 15:21:23 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/12 21:05:33 by mhonchar         ###   ########.fr       */
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

void		rt_mainloop(t_rt *rt, Uint32 *pixels)
{
	t_ray		ray;
	t_channel	color;
	int			x;
	int			y;
	double		dist_range[2];

	dist_range[0] = 1;
	dist_range[1] = DBL_MAX;
	ray.origin = rt->camera.origin;
	x = -CW / 2 - 1;
	while (++x <= CW / 2)
	{
		y = -CH / 2 - 1;
		while (++y <= CH / 2)
		{
			ray.direction = rt_canvas_to_viewport(x, y);
			ray.direction = rt_rotate_camera(&(rt->camera), ray.direction);
			color = rt_trace_ray(ray, rt, dist_range, RECURTION_DEPTH);
			ft_pp_img(pixels, x + CW / 2, CH / 2 - y,
				rt_channel_color_to_uint(color));
		}
	}
}
