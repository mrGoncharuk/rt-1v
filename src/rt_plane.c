/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:52:26 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/12 17:03:56 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	rt_calc_plane_normal(t_intersect *inter, t_ray ray)
{
	double	d_dot_n;

	d_dot_n = dot(ray.direction, inter->closest_obj->orient);
	if (d_dot_n < 0)
		return (inter->closest_obj->orient);
	return (-inter->closest_obj->orient);
}

void	rt_intersect_ray_plane(t_ray ray, t_objects *plane,
					t_intersect *inter, double *dist_range)
{
	double	t;
	double	denominator;
	t_vec	oc;

	denominator = dot(plane->orient, ray.direction);
	if (denominator != 0)
	{
		oc = (plane->orient - plane->centre);
		t = -dot(oc, plane->orient) / denominator;
		if (t > dist_range[0] && t < dist_range[1] && t < inter->dist)
		{
			inter->dist = t;
			inter->closest_obj = plane;
		}
	}
}
