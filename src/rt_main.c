/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 15:24:31 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/22 22:30:48 by mhonchar         ###   ########.fr       */
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
	o->next = (t_objects *)malloc(sizeof(t_objects));
	o = o->next;
	o->type = OBJ_SPHERE;
	o->centre = (t_vec) {1.4, 0, 4};
	o->radius = 1;
	o->color = (t_channel) {255, 255, 0};
	o->next = NULL;
}

void	rt_load_lights(t_lights **lights)
{
	t_lights	*l;

	*lights = (t_lights *)malloc(sizeof(t_lights));
	l = *lights;
	l->type = LT_AMBIENT;
	l->intensity = 0.2;
	l->next = (t_lights *)malloc(sizeof(t_lights));

	l = l->next;
	l->type = LT_POINT;
	l->intensity = 0.6;
	l->position = (t_vec) {2, 1, 0};
	l->next = (t_lights *)malloc(sizeof(t_lights));

	l = l->next;
	l->type = LT_DIRECT;
	l->intensity = 0.2;
	l->direction = (t_vec) {1, 4, 4};
	l->next = NULL;
}

void		rt_intersect_ray(t_ray ray, t_objects *objs, t_intersect *inter, double *dist_range)
{
	if (objs->type == OBJ_SPHERE)
		rt_intersect_ray_sphere(ray, objs, inter, dist_range);

}

/*
t_channel	rt_trace_ray(t_ray ray, t_objects *objs, t_lights *lights, double *dist_range)
{
	double		closest_t;
	t_objects	*closest_obj;
	t_vec		t;

	closest_t = DBL_MAX;
	closest_obj = NULL;
	while (objs)
	{
		t = rt_intersect_ray(ray, objs);
		if (t.x >= dist_range[0] && t.x <= dist_range[1] && t.x < closest_t)
		{
			closest_t = t.x;
			closest_obj = objs;
		}
		if (t.y >= dist_range[0] && t.y <= dist_range[1] && t.y < closest_t)
		{
			closest_t = t.y;
			closest_obj = objs;
		}
		objs = objs->next;
	}

	if (!closest_obj)
		return ((t_channel) {255, 255, 255});
	t_vec	hit;
	t_vec	normal;

	hit = ray.origin + closest_t * ray.direction;
	normal = hit - closest_obj->centre;
	//rt_enlightenment(closest_obj->color, rt_compute_lighting(lights, hit, normal));
	return (rt_enlightenment(closest_obj->color, rt_compute_lighting(lights, hit, normal)));
}
*/

t_vec		rt_calc_normal(t_intersect *inter)
{
	t_vec	normal;

	if (inter->closest_obj->type == OBJ_SPHERE)
	{
		normal = inter->hit - inter->closest_obj->centre;
		return (normal);
	}
	else
		return (0);
}

t_channel	rt_trace_ray(t_ray ray, t_objects *objs, t_lights *lights, double *dist_range)
{
	t_intersect	inter;
	double		i;

	inter.closest_obj = NULL;
	inter.dist = DBL_MAX;
	while(objs)
	{
		rt_intersect_ray(ray, objs, &inter, dist_range);
		objs = objs->next;
	}
	if (!inter.closest_obj)
		return ((t_channel) {255, 255, 255});
	inter.hit = ray.origin + inter.dist * ray.direction;
	inter.normal = rt_calc_normal(&inter);
	i = rt_compute_lighting(lights, inter.hit, inter.normal);
	return (rt_enlightenment(inter.closest_obj->color, i));
}



void	rt_mainloop(t_rt *rt, t_canvas *cn)
{
	t_ray		ray;
	t_channel		color;
	int			x;
	int			y;
	double		dist_range[2];

	dist_range[0] = 1;
	dist_range[1] = 2;
	ray.origin = 0;
	x = -CW / 2 - 1;
	while (++x < CW / 2)
	{
		y = -CH / 2 - 1;
		while (++y < CH / 2)
		{
			ray.direction = rt_canvas_to_viewport(x, y);
			color = rt_trace_ray(ray, rt->objs, rt->lights, dist_range);
			ft_pp_img(cn, x + CW / 2, CH / 2 - y, rt_channel_color_to_uint(color));
		}
	}
}

