/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 20:48:06 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/22 22:30:22 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	vec_length(t_vec v)
{
	return (sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
}

double		rt_compute_lighting(t_lights *lights, t_vec hit, t_vec normal)
{
	double	i;
	t_vec	l;
	double	numerator;

	i = 0.0;
	while (lights)
	{
		if (lights->type == LT_AMBIENT)
			i += lights->intensity;
		else 
		{
			if (lights->type == LT_POINT)
				l = lights->position - hit;
			else
				l = lights->direction;
			numerator = dot(normal, l);
			if (numerator > 0)
				i += lights->intensity * numerator / (vec_length(normal) * vec_length(l));
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
