/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:52:26 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/19 17:09:17 by dmolyboh         ###   ########.fr       */
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
	double	d[2];
	t_vec	oc[2];

	d[1] = dot(plane->orient, ray.direction);
	if (d[1] != 0)
	{
		oc[0] = ray.origin - plane->centre;
		d[0] = -dot(oc[0], plane->orient) / d[1];
		if (d[0] > dist_range[0] && d[0] < dist_range[1] && d[0] < inter->dist)
		{
			if (plane->radius > 0)
			{
				d[0] = -dot(oc[0], plane->orient) /
				dot(ray.direction, plane->orient);
				oc[1] = d[0] * ray.direction + oc[0];
				if (vec_length(oc[1]) < plane->radius)
					inter->dist = d[0];
				else
					return ;
			}
			else
				inter->dist = d[0];
			inter->closest_obj = plane;
		}
	}
}
