/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 15:17:35 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/21 19:06:33 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	rt_intersect_ray_sphere(t_ray ray, t_objects *objs)
{
	t_vec	t;
	t_vec	oc;
	t_vec	coeff;
	double	discriminant;

	oc = ray.origin - objs->centre;
	coeff.x = dot(ray.direction, ray.direction);
	coeff.y = 2 * dot(oc, ray.direction);
	coeff.z = dot(oc, oc) - objs->radius * objs->radius;
	discriminant = coeff.y * coeff.y - 4 * coeff.x * coeff.z;
	if (discriminant < 0)
	{
		t.x = DBL_MAX;
		t.y = DBL_MAX;
	}
	else
	{
		t.x = (-coeff.y + sqrt(discriminant)) / (2 * coeff.x);
		t.y = (-coeff.y - sqrt(discriminant)) / (2 * coeff.x);
		// printf("x: %d    y: %d    t1: %f    t2: %f\n",ray.x + CW / 2, CH / 2 - ray.y, t.x, t.y);
	}
	return (t);
}