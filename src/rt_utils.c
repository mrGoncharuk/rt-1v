/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 15:21:23 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/25 21:27:41 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec		rt_calc_normal(t_intersect *inter, t_ray ray)
{
	t_vec	normal;
	double	len;
	double	m;

	if (inter->closest_obj->type == OBJ_SPHERE)
	{
		normal = inter->hit - inter->closest_obj->centre;
		if ((len = vec_length(normal)) == 1)
			return (normal);
		else
			return (normal / vec_length(normal));
	}
	else if (inter->closest_obj->type == OBJ_PLANE)
		return (inter->closest_obj->normal);					//return (-inter->closest_obj->normal);
	else if (inter->closest_obj->type == OBJ_CYL)
	{
		m = dot(ray.direction, inter->closest_obj->normal) * inter->dist + dot((ray.origin - inter->closest_obj->centre), inter->closest_obj->normal);
		normal = inter->hit - inter->closest_obj->centre - inter->closest_obj->normal * m;
		return (normal / vec_length(normal));
	}
	else
		return (0);
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
