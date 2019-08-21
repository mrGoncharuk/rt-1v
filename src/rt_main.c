/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 15:24:31 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/21 19:08:47 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdio.h>

double	dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	rt_canvas_to_viewport(int x, int y)
{
	return ((t_vec){(double)x * (double)VIEWPORT_WIDTH / (double)CW, (double)y * (double)VIEWPORT_HEIGHT / (double)CH, DIST_CAM_PP});
}

void	rt_load_objects(t_objects **objs, const char *fname)
{
	t_objects *o;

	(void)fname;
	*objs = (t_objects *)malloc(sizeof(t_objects));
	o = *objs;
	o->type = OBJ_SPHERE;
	o->centre = (t_vec) {0, -1, 3};
	o->radius = 1;
	o->color = (t_channel) {255, 0, 0};
	o->next = NULL;
}

t_vec		rt_intersect_ray(t_ray ray, t_objects *objs)
{
	t_vec	t;

	t = DBL_MAX;
	if (objs->type == OBJ_SPHERE)
		t = rt_intersect_ray_sphere(ray, objs);
	return (t);
}

t_channel	rt_trace_ray(t_ray ray, t_objects *objs, double t_min, double t_max)
{
	double		closest_t;
	t_objects	*closest_obj;
	t_vec		t;
	int			i;

	closest_t = DBL_MAX;
	closest_obj = NULL;
	i = -1;
	while (objs)
	{
		t = rt_intersect_ray(ray, objs);
		if (t.x >= t_min && t.x <= t_max && t.x < closest_t)
		{
			closest_t = t.x;
			closest_obj = objs;
		}
		if (t.y >= t_min && t.y <= t_max && t.y < closest_t)
		{
			closest_t = t.y;
			closest_obj = objs;
		}
		objs = objs->next;
	}
	if (!closest_obj)
		return ((t_channel) {255, 255, 255});
	
	return (closest_obj->color);
}


void	rt_mainloop(t_rt *rt, t_canvas *cn)
{
	t_ray		ray;
	t_channel		color;
	int			x;
	int			y;

	ray.origin = 0;
	x = -CW / 2 - 1;
	while (++x < CW / 2)
	{
		y = -CH / 2 - 1;
		while (++y < CH / 2)
		{
			ray.direction = rt_canvas_to_viewport(x, y);
			color = rt_trace_ray(ray, rt->objs, 1, DBL_MAX);
			ft_pp_img(cn, x + CW / 2, CH / 2 - y, rt_channel_color_to_uint(color));
		}
	}
}

