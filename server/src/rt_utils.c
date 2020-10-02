/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 15:21:23 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/20 15:21:47 by dmolyboh         ###   ########.fr       */
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

t_vec		normalize(t_vec vec)
{
	double	length;

	length = vec_length(vec);
	if (length == 0)
		return (0);
	else
		return (vec / length);
}
