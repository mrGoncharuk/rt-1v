/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_objs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 12:02:05 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/28 14:14:58 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	pr_obj_sphere(const JSON_Object *j_ob, t_objects *sphere)
{
	if (!pr_vec_field(j_ob, "centre", &(sphere->centre)) ||
		!pr_vec_field(j_ob, "normal", &(sphere->normal)) ||
		!pr_channel_color(j_ob, sphere) ||
		!pr_specular(j_ob, sphere) ||
		!pr_radius(j_ob, sphere) ||
		!pr_reflection(j_ob, sphere))
		return (false);
	sphere->normal /= vec_length(sphere->normal);
	return (true);
}

bool	pr_obj_plane(const JSON_Object *j_ob, t_objects *plane)
{
	if (!pr_vec_field(j_ob, "centre", &(plane->centre)) ||
		!pr_vec_field(j_ob, "normal", &(plane->normal)) ||
		!pr_channel_color(j_ob, plane) ||
		!pr_specular(j_ob, plane) ||
		!pr_reflection(j_ob, plane))
		return (false);
	plane->normal /= vec_length(plane->normal);
	return (true);
}

bool	pr_obj_cyl(const JSON_Object *j_ob, t_objects *cyl)
{
	if (!pr_vec_field(j_ob, "centre", &(cyl->centre)) ||
		!pr_vec_field(j_ob, "normal", &(cyl->normal)) ||
		!pr_channel_color(j_ob, cyl) ||
		!pr_specular(j_ob, cyl) ||
		!pr_radius(j_ob, cyl) ||
		!pr_reflection(j_ob, cyl))
		return (false);
	cyl->normal /= vec_length(cyl->normal);
	return (true);
}

bool	pr_obj_cone(const JSON_Object *j_ob, t_objects *cone)
{
	if (!pr_vec_field(j_ob, "centre", &(cone->centre)) ||
		!pr_vec_field(j_ob, "normal", &(cone->normal)) ||
		!pr_channel_color(j_ob, cone) ||
		!pr_specular(j_ob, cone) ||
		!pr_angle(j_ob, cone) ||
		!pr_reflection(j_ob, cone))
		return (false);
	cone->normal /= vec_length(cone->normal);
	cone->k = 1 + pow(tan(cone->radius / 2), 2);
	return (true);
}
