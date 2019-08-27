/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:46:34 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/27 21:08:48 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	Fail when: there is no string value at key 'type';
**	given value string have unknown object type;
**	Success values: sphere, plane, cylinder, cone;
*/

bool	pr_object_type(const JSON_Object *j_ob, t_objects *obj)
{
	const char	*obj_type = json_object_get_string(j_ob, "type");

	if (obj_type == NULL)
		return false;
	else if (ft_strcmp(obj_type, "sphere") == 0)
		obj->type = OBJ_SPHERE;
	else if (ft_strcmp(obj_type, "plane") == 0)
		obj->type = OBJ_PLANE;
	else if (ft_strcmp(obj_type, "cylinder") == 0)
		obj->type = OBJ_CYL;
	else if (ft_strcmp(obj_type, "cone") == 0)
		obj->type = OBJ_CONE;
	else
		return (false);
	return (true);
}

/*
**	Fail when: there is no array value at key 'field_name';
**	array size != 3;
**	array values not number type;
**	Success values: any range number
*/

bool	pr_vec_field(const JSON_Object *j_ob, const char *field_name, t_vec *vec)
{
	JSON_Array	*j_arr;
	JSON_Value	*j_val;
	size_t		i;
	t_vec		v;

	if ((j_arr = json_object_get_array(j_ob, field_name)) == NULL)
		return (false);
	if (json_array_get_count(j_arr) != 3)
		return (false);
	i = 0;
	while (i < 3)
	{
		j_val = json_array_get_value(j_arr, i);
		if (json_value_get_type(j_val) != JSONNumber)
		{
			json_value_free(j_val);
			return (false);
		}
		v[i] = json_value_get_number(j_val);
		json_value_free(j_val);
		i++;
	}
	*vec = v;
	return (true);
}

/*
**	TODO: validate value type of array objects
*/


bool	pr_channel_color(const JSON_Object *j_ob, t_objects *obj)
{
	JSON_Array	*j_arr;

	if ((j_arr = json_object_get_array(j_ob, "color")) == NULL)
		return (false);
	if (json_array_get_count(j_arr) != 3)
		return (false);
	obj->color.r = (int)json_array_get_number(j_arr, 0);
	if (obj->color.r < 0)
		obj->color.r = 0;
	else if (obj->color.r > 255)
		obj->color.r = 255;
	obj->color.g = (int)json_array_get_number(j_arr, 1);
	if (obj->color.g < 0)
		obj->color.g = 0;
	else if (obj->color.g > 255)
		obj->color.g = 255;
	obj->color.b = (int)json_array_get_number(j_arr, 2);
	if (obj->color.b < 0)
		obj->color.b = 0;
	else if (obj->color.b > 255)
		obj->color.b = 255;
}

/*
**	Fail when: there is no number value at key 'specular';
**	Success values: any range number
*/

bool	pr_specular(const JSON_Object *j_ob, t_objects *obj)
{
	if (!json_object_has_value_of_type(j_ob, "specular", JSONNumber))
		return (false);
	obj->specular = json_object_get_number(j_ob, "specular");
	return (true);
}

/*
**	Fail when: there is no number value at key 'specular';
**	number out of range [0; 1]
**	Success values: range of [0; 1]
*/

bool	pr_reflection(const JSON_Object *j_ob, t_objects *obj)
{
	if (!json_object_has_value_of_type(j_ob, "reflection", JSONNumber))
		return (false);
	obj->reflection = json_object_get_number(j_ob, "reflection");
	if (obj->reflection > 1 || obj->reflection < 0)
		return (false);
	return (true);
}

/*
**	Fail when: there is no number value at key 'radius';
**	number <= 0
**	Success values: positive number greater than 0
*/

bool	pr_radius(const JSON_Object *j_ob, t_objects *obj)
{
	if (!json_object_has_value_of_type(j_ob, "radius", JSONNumber))
		return (false);
	if ((obj->radius = json_object_get_number(j_ob, "radius")) <= 0)
		return (false);
	return (true);
}

bool	pr_obj_sphere(const JSON_Object *j_ob, t_objects *sphere)
{
	if (!pr_vec_field(j_ob, "centre", &(sphere->centre)) ||
		!pr_vec_field(j_ob, "normal", &(sphere->normal)) ||
		!pr_channel_color(j_ob, sphere) ||
		!pr_specular(j_ob, sphere) ||
		!pr_radius(j_ob, sphere))
		return (false);
	sphere->normal /= vec_length(sphere->normal);
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

bool	pr_obj_cone(const JSON_Object *j_ob, t_objects *cone)
{
	if (!pr_vec_field(j_ob, "centre", &(cone->centre)) ||
		!pr_vec_field(j_ob, "normal", &(cone->normal)) ||
		!pr_channel_color(j_ob, cone) ||
		!pr_specular(j_ob, cone) ||
		!pr_angle(j_ob, cone))
		return (false);
	cone->normal /= vec_length(cone->normal);
	return (true);
}

t_objects	*parse_array_of_scene_objects(JSON_Array *objs_arr)
{
	t_objects	*objs;

	objs = json_array_get_object(objs_arr, 0);
	printf("Object type is: %f \n", json_object_get_number(objs, "radius"));
	return (NULL);
}


int		main(void)
{
	JSON_Value	*json_val;
	JSON_Object *json_objs;
	JSON_Array	*json_arr;
    size_t i;

    char output_filename[] = "scene.json";
	if ((json_val = json_parse_file(output_filename)) == NULL)
	{
		printf("Error while parsing json\n");
		return (-1);
	}
	if ((json_objs = json_value_get_object(json_val)) == NULL)
	{
		printf("Error while getting object from value\n");
		return (-1);
	}
	if ((json_arr = json_object_get_array(json_objs, "objects")) == NULL)
	{
		printf("Error while getting array of scene objects\n");
		return (-1);
	}
	parse_array_of_scene_objects(json_arr);
	printf("All good so far\n");

	return (0);
}