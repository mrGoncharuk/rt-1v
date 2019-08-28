/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_rt_scene_loader.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 15:18:24 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/28 16:45:32 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	o->centre = (t_vec) {-2, 0, 4};
	o->radius = 1;
	o->color = (t_channel) {0, 255, 0};
	o->specular = 500;
	o->reflection = 0.4;
	o->next = (t_objects *)malloc(sizeof(t_objects));

	// o = o->next;
	// o->type = OBJ_SPHERE;
	// o->color = (t_channel) {255, 255, 1};
	// o->centre = (t_vec) {0, -5001, 0};
	// o->radius = 5000;
	// o->specular = 1000;
	// o->reflection = 0.5;
	// o->next = (t_objects *)malloc(sizeof(t_objects));
	
	o = o->next;	
	o->type = OBJ_SPHERE;
	o->centre = (t_vec) {2, 0, 4};
	o->radius = 1;
	o->color = (t_channel) {0, 0, 255};
	o->specular = 10;
	o->reflection = 0.3;
	o->next = (t_objects *)malloc(sizeof(t_objects));


	o = o->next;
	o->type = OBJ_PLANE;
	o->centre = (t_vec) {0, 0, 100};
	o->color = (t_channel) {255, 255, 255};
	o->orient = (t_vec) {0, 0, 1};
	o->specular = 10;
	o->reflection = 0;
	o->next = (t_objects *)malloc(sizeof(t_objects));

	o = o->next;
	o->type = OBJ_PLANE;
	o->centre = (t_vec) {0, 3, 0};
	o->color = (t_channel) {125, 25, 55};
	o->orient = (t_vec) {0, 1, 0};
	o->specular = 0;
	o->reflection = 0;
	o->next = (t_objects *)malloc(sizeof(t_objects));


	o = o->next;
	o->type = OBJ_CYL;
	o->centre = (t_vec) {-2, 2, 10};
	o->color = (t_channel) {66, 255, 120};
	o->orient = (t_vec) {0, 1, 0};
	o->radius = 0.6;
	o->specular = 10;
	o->reflection = 0;
	o->next = (t_objects *)malloc(sizeof(t_objects));
	
	o = o->next;
	o->type = OBJ_CONE;
	o->centre = (t_vec) {3, 0, 10};
	o->color = (t_channel) {200, 200, 69};
	o->orient = (t_vec) {0, 1, 0};
	o->radius = M_PI;				//   pi/3
	o->specular = 30;
	o->reflection = 0;
	o->k = (1 + pow(tan(o->radius / 2), 2));
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
	l->position = (t_vec) {2, 7, 0};
	l->next = (t_lights *)malloc(sizeof(t_lights));

	l = l->next;
	l->type = LT_DIRECT;
	l->intensity = 0.2;
	l->direction = (t_vec) {1, 4, 4};
	l->next = NULL;
}