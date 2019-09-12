/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 20:48:06 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/12 19:13:09 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_channel	rt_calc_reflected_color(t_channel local_color,
				t_channel reflected_color, double r)
{
	local_color.r = local_color.r * (1 - r) + reflected_color.r * r;
	local_color.g = local_color.g * (1 - r) + reflected_color.g * r;
	local_color.b = local_color.b * (1 - r) + reflected_color.b * r;
	return (local_color);
}

double		rt_calc_specularity(t_vec normal, t_vec light, t_vec v, double spec)
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

bool		rt_point_in_shadow(t_objects *objs, t_vec point, t_vec light,
								int l_type)
{
	double		dist_range[2];
	t_intersect	inter;
	t_ray		ray;

	ray.origin = point;
	ray.direction = light;
	inter.dist = DBL_MAX;
	inter.closest_obj = NULL;
	dist_range[0] = 0.0001;
	dist_range[1] = (l_type == LT_POINT) ? 1 : DBL_MAX;
	while (objs)
	{
		rt_intersect_ray(ray, objs, &inter, dist_range);
		if (inter.closest_obj != NULL)
			return (true);
		objs = objs->next;
	}
	return (false);
}

double		rt_calc_intesity(t_lights *light, t_ray r, t_vec l, t_intersect *in)
{
	double	numerator;
	double	i;

	i = 0;
	numerator = dot(in->normal, l);
	if (numerator > 0)
		i += light->intensity * numerator / (vec_length(in->normal) *
				vec_length(l));
	if (in->closest_obj->specular > 0)
		i += light->intensity * rt_calc_specularity(in->normal, l,
				-r.direction, in->closest_obj->specular);
	return (i);
}

double		rt_compute_lighting(t_objects *objs, t_lights *lights,
			t_ray ray, t_intersect *inter)
{
	double	i;
	t_vec	l;

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
			l = l / vec_length(l);
			if (rt_point_in_shadow(objs, inter->hit, l, lights->type))
			{
				lights = lights->next;
				continue;
			}
			i += rt_calc_intesity(lights, ray, l, inter);
		}
		lights = lights->next;
	}
	return (i);
}
