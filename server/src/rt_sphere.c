/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaniche <khaniche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 15:17:35 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/15 16:58:00 by khaniche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec			rt_calc_sphere_normal(t_intersect *inter)
{
	t_vec	normal;

	normal = inter->hit - inter->closest_obj->centre;
	return (normal / vec_length(normal));
}

double			rt_select_dist(double *roots, double *dist_range)
{
	double	best;

	best = DBL_MAX;
	if (roots[0] > dist_range[0] && roots[0] < dist_range[1])
		best = roots[0];
	if (roots[1] > dist_range[0] && roots[1] < dist_range[1] && roots[1] < best)
		best = roots[1];
	return (best);
}

void			rt_intersect_ray_sphere(t_ray ray, t_objects *sphere,
					t_intersect *inter, double *dist_range)
{
	double	roots[2];
	t_vec	oc;
	t_vec	coeff;
	double	discriminant;
	double	curr_t;

	oc = ray.origin - sphere->centre;
	coeff.x = dot(ray.direction, ray.direction);
	coeff.y = 2 * dot(oc, ray.direction);
	coeff.z = dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = coeff.y * coeff.y - 4 * coeff.x * coeff.z;
	if (discriminant >= 0)
	{
		roots[0] = (-coeff.y + sqrt(discriminant)) / (2 * coeff.x);
		roots[1] = (-coeff.y - sqrt(discriminant)) / (2 * coeff.x);
		curr_t = rt_select_dist(roots, dist_range);
		if (curr_t < inter->dist)
		{
			inter->dist = curr_t;
			inter->closest_obj = sphere;
		}
	}
}
