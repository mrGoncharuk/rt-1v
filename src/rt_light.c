/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 20:48:06 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/23 17:10:44 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	vec_length(t_vec v)
{
	return (sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
}

double		rt_calc_specularity(t_vec normal, t_vec light, t_vec v, int spec)
{
	double	i;
	t_vec	reflect;
	double	numerator;

	i = 0;
	reflect = 2 * normal * dot(normal, light) - light;
	numerator = dot(reflect, v);
	if (numerator > 0)
		i = pow((numerator / (vec_length(reflect) * vec_length(v))), spec);
	return (i);
}


bool		rt_point_in_shadow(t_objects *objs, t_vec point, t_vec light)
{
	double	dist_range[2];
	t_intersect	inter;
	t_ray		ray;

	ray.origin = point;
	ray.direction = light;
	inter.dist = DBL_MAX;
	inter.closest_obj = NULL;
	dist_range[0] = 0.001;
	dist_range[1] = DBL_MAX;
	rt_intersect_ray(ray, objs, &inter, dist_range);
	if (inter.closest_obj == NULL)
		return (false);
	else
		return (true);

}
double		rt_compute_lighting(t_objects *objs, t_lights *lights, t_ray ray, t_intersect *inter)
{
	double	i;
	t_vec	l;
	double	numerator;

	(void)ray;
	i = 0.0;
	while (lights)
	{
		if (lights->type == LT_AMBIENT)
			i += lights->intensity;
		else 
		{
			if (lights->type == LT_POINT)
				l = lights->position - inter->hit;
			else
				l = lights->direction;
			numerator = dot(inter->normal, l);
			if (rt_point_in_shadow(objs, inter->hit, l))
			{
				lights = lights->next;
				continue;
			}
			if (numerator > 0)
				i += lights->intensity * numerator / (vec_length(inter->normal) * vec_length(l));
			if (inter->closest_obj->specular != -1)
				i += lights->intensity * rt_calc_specularity(inter->normal, l, -ray.direction, inter->closest_obj->specular);
		}
		lights = lights->next;
	}
	return (i);
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
