/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 20:16:47 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/25 21:25:23 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	rt_select_dist(double *roots, double *dist_range)
{
	if (roots[1] < dist_range[0] && roots[0] < dist_range[0])
		return (DBL_MAX);
	if (roots[1] < roots[0])
		return (roots[1]);
	else
		return (roots[0]);
}

void	rt_intersect_ray_cylinder(t_ray ray, t_objects *cyl,
					t_intersect *inter, double *dist_range)
{
	double	roots[2];
	t_vec	oc;
	t_vec	coeff;
	double	discriminant;
	double	curr_t;

	oc = ray.origin - cyl->centre;
	coeff[0] = dot(ray.direction, ray.direction) - pow(dot(ray.direction, cyl->normal), 2);
	coeff[1] = dot(ray.direction, oc) - dot(ray.direction, cyl->normal) * dot(oc, cyl->normal);
	coeff[2] = dot(oc, oc) - pow(dot(oc, cyl->normal), 2) - cyl->radius;
	discriminant = coeff.y * coeff.y - 4 * coeff.x * coeff.z;
	if (discriminant > 0)
	{
		roots[0] = (-coeff.y + sqrt(discriminant)) / (2 * coeff.x);
		roots[1] = (-coeff.y - sqrt(discriminant)) / (2 * coeff.x);
		curr_t = rt_select_dist(roots, dist_range);
		// if (curr_t < inter->dist)
		// {
			inter->dist = curr_t;
			inter->closest_obj = cyl;
		// }
	}
}