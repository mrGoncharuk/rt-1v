/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_figure_defenetion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 10:43:28 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/09/18 15:13:28 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		rt_intersect_ray(t_ray ray, t_objects *objs, t_intersect *inter,
				double *dist_range)
{
	if (objs->type == OBJ_SPHERE)
		rt_intersect_ray_sphere(ray, objs, inter, dist_range);
	else if (objs->type == OBJ_PLANE)
		rt_intersect_ray_plane(ray, objs, inter, dist_range);
	else if (objs->type == OBJ_CYL)
		rt_intersect_ray_cylinder(ray, objs, inter, dist_range);
	else if (objs->type == OBJ_CONE)
		rt_intersect_ray_cone(ray, objs, inter, dist_range);
	else if (objs->type == OBJ_PAR)
		rt_intersect_ray_par(ray, objs, inter, dist_range);
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
	else if (inter->closest_obj->type == OBJ_PAR)
		return (rt_calc_par_normal(inter, ray));
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
