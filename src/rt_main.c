/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 15:24:31 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/23 21:18:34 by mhonchar         ###   ########.fr       */
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
	o->specular = 500;
	o->reflection = 0.2;
	o->next = (t_objects *)malloc(sizeof(t_objects));
	
	o = o->next;
	o->type = OBJ_SPHERE;
	o->centre = (t_vec) {-1.5, 0, 4};
	o->radius = 1;
	o->color = (t_channel) {0, 0, 255};
	o->specular = 500;
	o->reflection = 0.3;
	o->next = (t_objects *)malloc(sizeof(t_objects));

	o = o->next;
	o->type = OBJ_SPHERE;
	o->centre = (t_vec) {1.5, 0, 4};
	o->radius = 1;
	o->color = (t_channel) {0, 255, 0};
	o->specular = 500;
	o->reflection = 0.4;
	o->next = (t_objects *)malloc(sizeof(t_objects));

	o = o->next;
	o->type = OBJ_SPHERE;
	o->color = (t_channel) {255, 255, 0};
	o->centre = (t_vec) {0, -5001, 0};
	o->radius = 5000;
	o->specular = 1000;
	o->reflection = 0.5;
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

t_vec		rt_reflect_ray(t_vec normal, t_vec ray_dir)
{
	return (2 * normal * dot(normal, ray_dir) - ray_dir);
}

t_channel	rt_calc_reflected_color(t_channel local_color, t_channel reflected_color, double r)
{	
	local_color.r = local_color.r * (1 - r) + reflected_color.r * r;
	local_color.g = local_color.g * (1 - r) + reflected_color.g * r;
	local_color.b = local_color.b * (1 - r) + reflected_color.b * r;
	return (local_color);
}

t_channel	rt_trace_ray(t_ray ray, t_objects *objs, t_lights *lights, double *dist_range, int depth)
{
	t_channel	local_color;
	t_channel	reflected_color;
	t_intersect	inter;
	double		i;
	t_objects	*objs_head;

	inter.closest_obj = NULL;
	inter.dist = DBL_MAX;
	objs_head = objs;
	while(objs)
	{
		rt_intersect_ray(ray, objs, &inter, dist_range);
		objs = objs->next;
	}
	if (!inter.closest_obj)
		return ((t_channel) {0, 0, 0});
	inter.hit = ray.origin + inter.dist * ray.direction;
	inter.normal = rt_calc_normal(&inter);
	i = rt_compute_lighting(objs_head, lights, ray, &inter);
	local_color = rt_enlightenment(inter.closest_obj->color, i);

	if (depth <= 0 || inter.closest_obj->reflection <= 0)
		return	(local_color);
	ray.direction = rt_reflect_ray(inter.normal, -ray.direction);
	ray.origin = inter.hit;
	reflected_color = rt_trace_ray(ray, objs_head, lights, (double []) {0.001, DBL_MAX}, depth - 1);
	return (rt_calc_reflected_color(local_color, reflected_color, inter.closest_obj->reflection));
}



void	rt_mainloop(t_rt *rt, t_canvas *cn)
{
	t_ray		ray;
	t_channel	color;
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
			color = rt_trace_ray(ray, rt->objs, rt->lights, dist_range, RECURTION_DEPTH);
			ft_pp_img(cn, x + CW / 2, CH / 2 - y, rt_channel_color_to_uint(color));
		}
	}
}

