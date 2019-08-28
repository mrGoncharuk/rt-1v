/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 20:16:47 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/28 16:40:51 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec			rt_calc_cylinder_normal(t_intersect *i, t_ray ray)
{
	t_vec	normal;
	double	m;

	m = dot(ray.direction, i->closest_obj->orient) * i->dist +
		dot((ray.origin - i->closest_obj->centre), i->closest_obj->orient);
	normal = i->hit - i->closest_obj->centre -
		i->closest_obj->orient * m;
	return (normal / vec_length(normal));
}

static double	rt_select_dist(double *roots, double *dist_range)
{
	if (roots[1] < dist_range[0] && roots[0] < dist_range[0])
		return (DBL_MAX);
	if (roots[1] < roots[0])
		return (roots[1]);
	else
		return (roots[0]);
}

void			rt_intersect_ray_cylinder(t_ray ray, t_objects *cyl,
					t_intersect *inter, double *dist_range)
{
	double	roots[2];
	t_vec	oc;
	t_vec	coeff;
	double	discriminant;
	double	curr_t;

	oc = ray.origin - cyl->centre;
	coeff[0] = dot(ray.direction, ray.direction) -
				pow(dot(ray.direction, cyl->orient), 2);
	coeff[1] = 2 * (dot(ray.direction, oc) -
				dot(ray.direction, cyl->orient) * dot(oc, cyl->orient));
	coeff[2] = dot(oc, oc) - pow(dot(oc, cyl->orient), 2) - cyl->radius;
	discriminant = coeff.y * coeff.y - 4 * coeff.x * coeff.z;
	if (discriminant > 0)
	{
		roots[0] = (-coeff.y + sqrt(discriminant)) / (2 * coeff.x);
		roots[1] = (-coeff.y - sqrt(discriminant)) / (2 * coeff.x);
		curr_t = rt_select_dist(roots, dist_range);
		if (curr_t < inter->dist)
		{
			inter->dist = curr_t;
			inter->closest_obj = cyl;
		}
	}
}
