/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 15:24:31 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/27 20:52:36 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdio.h>

void		rt_intersect_ray(t_ray ray, t_objects *objs, t_intersect *inter,
				double *dist_range)
{
	if (objs->type == OBJ_SPHERE)
		rt_intersect_ray_sphere(ray, objs, inter, dist_range);
	if (objs->type == OBJ_PLANE)
		rt_intersect_ray_plane(ray, objs, inter, dist_range);
	if (objs->type == OBJ_CYL)
		rt_intersect_ray_cylinder(ray, objs, inter, dist_range);
	if (objs->type == OBJ_CONE)
		rt_intersect_ray_cone(ray, objs, inter, dist_range);
}

t_vec		rt_calc_normal(t_intersect *inter, t_ray ray)
{
	if (inter->closest_obj->type == OBJ_SPHERE)
		return (rt_calc_sphere_normal(inter));
	else if (inter->closest_obj->type == OBJ_PLANE)
		return (rt_calc_plane_normal(inter, ray));
	else if (inter->closest_obj->type == OBJ_CYL)
		return (rt_calc_cylinder_normal(inter, ray));
	else if (inter->closest_obj->type == OBJ_CONE)
		return (rt_calc_cone_normal(inter, ray));
	else
		return (0);
}

bool		rt_find_closest_obj(t_ray ray, t_objects *objs, t_intersect *inter,
				double *dist_range)
{
	inter->closest_obj = NULL;
	inter->dist = DBL_MAX;
	while (objs)
	{
		rt_intersect_ray(ray, objs, inter, dist_range);
		objs = objs->next;
	}
	return (inter->closest_obj != NULL);
}

t_channel	rt_trace_ray(t_ray ray, t_rt *rt, double *dist_range, int depth)
{
	t_channel	local_color;
	t_channel	reflected_color;
	t_intersect	inter;
	double		i;

	if (!rt_find_closest_obj(ray, rt->objs, &inter, dist_range))
		return ((t_channel) {0, 0, 0});
	inter.hit = ray.origin + inter.dist * ray.direction;
	inter.normal = rt_calc_normal(&inter, ray);
	i = rt_compute_lighting(rt->objs, rt->lights, ray, &inter);
	local_color = rt_enlightenment(inter.closest_obj->color, i);
	if (depth <= 0 || inter.closest_obj->reflection <= 0)
		return (local_color);
	ray.direction = rt_reflect_ray(inter.normal, -ray.direction);
	ray.origin = inter.hit;
	reflected_color = rt_trace_ray(ray, rt,
		(double[2]) {0.001, DBL_MAX}, depth - 1);
	return (rt_calc_reflected_color(local_color, reflected_color,
		inter.closest_obj->reflection));
}

void		rt_mainloop(t_rt *rt, t_canvas *cn)
{
	t_ray		ray;
	t_channel	color;
	int			x;
	int			y;
	double		dist_range[2];

	dist_range[0] = 1;
	dist_range[1] = DBL_MAX;
	ray.origin = (t_vec) {0, 0, -3};
	x = -CW / 2 - 1;
	while (++x < CW / 2)
	{
		y = -CH / 2 - 1;
		while (++y < CH / 2)
		{
			ray.direction = rt_canvas_to_viewport(x, y);
			color = rt_trace_ray(ray, rt, dist_range, RECURTION_DEPTH);
			ft_pp_img(cn, x + CW / 2, CH / 2 - y,
				rt_channel_color_to_uint(color));
		}
	}
}
