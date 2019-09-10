/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_fields2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 12:16:14 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/10 18:24:33 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	Fail when: there is no string value at key 'type';
**	given value string have unknown object type;
**	Success values: sphere, plane, cylinder, cone;
*/

bool	pr_object2(const JSON_Object *j_ob, t_objects *obj, const char *obj_t)
{
	if (ft_strcmp(obj_t, "cylinder") == 0)
	{
		obj->type = OBJ_CYL;
		if (!pr_obj_cyl(j_ob, obj))
			return (false);
	}
	else if (ft_strcmp(obj_t, "cone") == 0)
	{
		obj->type = OBJ_CONE;
		if (!pr_obj_cone(j_ob, obj))
			return (false);
	}
	else
		return (false);
	return (true);
}

bool	pr_object(const JSON_Object *j_ob, t_objects *obj)
{
	const char	*obj_type = json_object_get_string(j_ob, "type");

	if (obj_type == NULL)
		return (false);
	else if (ft_strcmp(obj_type, "sphere") == 0)
	{
		obj->type = OBJ_SPHERE;
		if (!pr_obj_sphere(j_ob, obj))
			return (false);
	}
	else if (ft_strcmp(obj_type, "plane") == 0)
	{
		obj->type = OBJ_PLANE;
		if (!pr_obj_plane(j_ob, obj))
			return (false);
	}
	else
		return (pr_object2(j_ob, obj, obj_type));
	return (true);
}

/*
**	Fail when: there is no string value at key 'type';
**	given value string have unknown light type;
**	Success values: ambient, point, direct;
*/

bool	pr_light(const JSON_Object *j_ob, t_lights *light)
{
	const char	*light_type = json_object_get_string(j_ob, "type");

	if (light_type == NULL)
		return (false);
	else if (ft_strcmp(light_type, "ambient") == 0)
	{
		light->type = LT_AMBIENT;
		if (!pr_light_ambient(j_ob, light))
			return (false);
	}
	else if (ft_strcmp(light_type, "point") == 0)
	{
		light->type = LT_POINT;
		if (!pr_light_point(j_ob, light))
			return (false);
	}
	else if (ft_strcmp(light_type, "direct") == 0)
	{
		light->type = LT_DIRECT;
		if (!pr_light_direct(j_ob, light))
			return (false);
	}
	else
		return (false);
	return (true);
}

/*
**	Fail when: there is no number value at key 'radius';
**	number out of range [1; 90]
**	Success values: positive number in range [1; 90]
*/

bool	pr_angle(const JSON_Object *j_ob, t_objects *obj)
{
	if (!json_object_has_value_of_type(j_ob, "angle", JSONNumber))
		return (false);
	obj->angle = json_object_get_number(j_ob, "angle");
	if ((obj->angle < 1) && (obj->angle > 90))
		return (false);
	obj->radius = DEG_TO_RAD(obj->angle);
	return (true);
}

/*
**	Fail when: there is no number value at key 'intensity';
**	number out of range [0; 1]
**	Success values: number in range of [0; 1]
*/

bool	pr_light_intensity(const JSON_Object *j_ob, t_lights *light)
{
	if (!json_object_has_value_of_type(j_ob, "intensity", JSONNumber))
		return (false);
	light->intensity = json_object_get_number(j_ob, "intensity");
	if (light->intensity > 1 || light->intensity < 0)
		return (false);
	return (true);
}
