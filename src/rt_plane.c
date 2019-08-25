/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:52:26 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/25 20:21:24 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_intersect_ray_plane(t_ray ray, t_objects *plane,
					t_intersect *inter, double *dist_range)
{
	double	t;
	double	denominator;

	denominator = dot(plane->normal, ray.direction);
	if (denominator != 0)
{
		t = (dot(plane->normal, plane->centre) - dot(ray.origin, plane->centre)) / denominator;
		if (t > dist_range[0] && t < dist_range[1] && t < inter->dist)
		{
			inter->dist = t;
			inter->closest_obj = plane;
		}
	}
}
