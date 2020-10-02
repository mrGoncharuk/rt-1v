/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_objs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 12:02:05 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/20 13:05:06 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	pr_obj_sphere(const JSON_Object *j_ob, t_objects *sphere)
{
	if (!pr_vec_field(j_ob, "centre", &(sphere->centre)) ||
		!pr_channel_color(j_ob, sphere) ||
		!pr_specular(j_ob, sphere) ||
		!pr_compose(j_ob, sphere) ||
		!pr_radius(j_ob, sphere) ||
		!pr_reflection(j_ob, sphere) ||
		!pr_texture(j_ob, sphere) ||
		!pr_transparency(j_ob, sphere) ||
		!check_reflect_transparency(sphere))
		return (false);
	sphere->orient /= vec_length(sphere->orient);
	return (true);
}

bool	pr_obj_plane(const JSON_Object *j_ob, t_objects *plane)
{
	if (!pr_vec_field(j_ob, "centre", &(plane->centre)) ||
		!pr_vec_field(j_ob, "orient", &(plane->orient)) ||
		!pr_channel_color(j_ob, plane) ||
		!pr_specular(j_ob, plane) ||
		!pr_texture(j_ob, plane) ||
		!pr_reflection(j_ob, plane) ||
		!pr_transparency(j_ob, plane) ||
		!check_reflect_transparency(plane))
		return (false);
	pr_negative(j_ob, plane);
	pr_radius_pl(j_ob, plane);
	if (vec_length(plane->orient) != 0)
		plane->orient /= vec_length(plane->orient);
	else
		plane->orient = 1;
	return (true);
}

bool	pr_obj_cyl(const JSON_Object *j_ob, t_objects *cyl)
{
	if (!pr_vec_field(j_ob, "centre", &(cyl->centre)) ||
		!pr_vec_field(j_ob, "orient", &(cyl->orient)) ||
		!pr_cut(j_ob, cyl) ||
		!pr_radius(j_ob, cyl) ||
		!pr_channel_color(j_ob, cyl) ||
		!pr_specular(j_ob, cyl) ||
		!pr_texture(j_ob, cyl) ||
		!pr_reflection(j_ob, cyl) ||
		!pr_transparency(j_ob, cyl) ||
		!check_reflect_transparency(cyl))
		return (false);
	if (vec_length(cyl->orient) != 0)
		cyl->orient /= vec_length(cyl->orient);
	else
		cyl->orient = 1;
	return (true);
}

bool	pr_obj_cone(const JSON_Object *j_ob, t_objects *cone)
{
	if (!pr_vec_field(j_ob, "centre", &(cone->centre)) ||
		!pr_vec_field(j_ob, "orient", &(cone->orient)) ||
		!pr_cut(j_ob, cone) ||
		!pr_channel_color(j_ob, cone) ||
		!pr_specular(j_ob, cone) ||
		!pr_angle(j_ob, cone) ||
		!pr_texture(j_ob, cone) ||
		!pr_transparency(j_ob, cone) ||
		!pr_reflection(j_ob, cone) ||
		!check_reflect_transparency(cone))
		return (false);
	if (vec_length(cone->orient) != 0)
		cone->orient /= vec_length(cone->orient);
	else
		cone->orient = 1;
	cone->k = 1 + pow(tan(cone->radius / 2), 2);
	return (true);
}

bool	pr_obj_par(const JSON_Object *j_ob, t_objects *par)
{
	if (!pr_vec_field(j_ob, "centre", &(par->centre)) ||
		!pr_vec_field(j_ob, "orient", &(par->orient)) ||
		!pr_cut(j_ob, par) ||
		!pr_channel_color(j_ob, par) ||
		!pr_specular(j_ob, par) ||
		!pr_angle(j_ob, par) ||
		!pr_texture(j_ob, par) ||
		!pr_transparency(j_ob, par) ||
		!pr_reflection(j_ob, par) ||
		!check_reflect_transparency(par))
		return (false);
	if (vec_length(par->orient) != 0)
		par->orient /= vec_length(par->orient);
	else
		par->orient = 1;
	return (true);
}
