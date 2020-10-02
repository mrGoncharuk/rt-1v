/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 20:48:06 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/20 15:22:54 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_channel			rt_calc_ref_tran_color(t_color_trace color,
						double r, double t)
{
	color.local_color.r = color.local_color.r * (1 - t) * (1 - r) +
		color.reflected_color.r * r + color.transparency_color.r * t;
	color.local_color.g = color.local_color.g * (1 - t) * (1 - r) +
		color.reflected_color.g * r + color.transparency_color.g * t;
	color.local_color.b = color.local_color.b * (1 - t) * (1 - r) +
		color.reflected_color.b * r + color.transparency_color.b * t;
	color.local_color = rt_enlightenment(color.local_color, 1);
	return (color.local_color);
}

double				rt_calc_specularity(t_vec normal, t_vec light,
			t_vec v, double spec)
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

double				rt_calc_intesity(t_lights *light, t_ray r, t_vec l,
			t_intersect *in)
{
	double		numerator;
	double		i;

	i = 0;
	numerator = dot(in->normal, l);
	if (numerator > 0)
		i += light->intensity * numerator / (vec_length(in->normal) *
				vec_length(l));
	if (in->closest_obj->specular > 0)
		i += (light->intensity * rt_calc_specularity(in->normal, l,
				-r.direction, in->closest_obj->specular));
	return (i);
}

static t_vec		rt_get_light_vector(t_lights *lights, t_intersect *inter)
{
	t_vec	l;

	if (lights->type == LT_POINT)
		l = lights->position - inter->hit;
	else
		l = lights->direction;
	return (normalize(l));
}

double				rt_compute_lighting(t_objects *objs, t_lights *lights,
			t_ray ray, t_intersect *inter)
{
	double		i;
	t_vec		l;
	t_objects	*sh_obj;

	i = 0.0;
	while (lights)
	{
		if (lights->type == LT_AMBIENT)
			i += lights->intensity;
		else
		{
			l = rt_get_light_vector(lights, inter);
			if ((sh_obj = rt_point_in_shadow(objs, inter->hit, l, *lights)))
			{
				if (sh_obj->transparency > 0)
					i += sh_obj->transparency *
						rt_calc_intesity(lights, ray, l, inter);
				lights = lights->next;
				continue;
			}
			i += rt_calc_intesity(lights, ray, l, inter);
		}
		lights = lights->next;
	}
	return (i);
}
