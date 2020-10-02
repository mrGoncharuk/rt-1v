/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cut_and_sort_roots.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 22:14:29 by khaniche          #+#    #+#             */
/*   Updated: 2019/09/18 12:53:39 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			rt_cut_figure(t_intersect *inter, double *data, t_objects *obj,
				t_ray ray)
{
	t_vec	oc;
	t_vec	hit;
	double	len;

	oc = ray.origin - obj->centre;
	if (data[0] < inter->dist)
	{
		hit = data[0] * ray.direction + oc;
		len = dot(hit, obj->orient);
		if (len > obj->cut[0] && len < obj->cut[1])
		{
			inter->dist = data[0];
			inter->closest_obj = obj;
		}
		else if (data[1] < inter->dist)
		{
			hit = data[1] * ray.direction + oc;
			len = dot(hit, obj->orient);
			if (len > obj->cut[0] && len < obj->cut[1])
			{
				inter->dist = data[1];
				inter->closest_obj = obj;
			}
		}
	}
}

void			rt_sort_roots(double *roots, double *dist_range)
{
	double	tmp;

	if (roots[0] < dist_range[0] || roots[0] > dist_range[1])
		roots[0] = DBL_MAX;
	if (roots[1] < dist_range[0] || roots[1] > dist_range[1])
		roots[1] = DBL_MAX;
	if (roots[0] > roots[1])
	{
		tmp = roots[0];
		roots[0] = roots[1];
		roots[1] = tmp;
	}
}
