/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_fields.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 12:02:08 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/11 20:14:03 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	Fail when: there is no array value at key 'field_name';
**	array size != 3;
**	array values not number type;
**	Success values: any range number
*/

bool	pr_vec_field(const JSON_Object *j_ob, const char *field_name, t_vec *v)
{
	JSON_Array	*j_arr;
	JSON_Value	*j_val;
	size_t		i;
	t_vec		vec;

	if ((j_arr = json_object_get_array(j_ob, field_name)) == NULL)
		return (false);
	if (json_array_get_count(j_arr) != 3)
		return (false);
	i = 0;
	while (i < 3)
	{
		j_val = json_array_get_value(j_arr, i);
		if (json_value_get_type(j_val) != JSONNumber)
			return (false);
		vec[i] = json_value_get_number(j_val);
		i++;
	}
	*v = vec;
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
	return (true);
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
**	Fail when: number out of range [-inf; 1]
**	Success values: number in range of [-inf; 1];
** 	there is no number value at key 'reflection',
**	in this case reflection value of object is -1;
*/

bool	pr_reflection(const JSON_Object *j_ob, t_objects *obj)
{
	if (!json_object_has_value_of_type(j_ob, "reflection", JSONNumber))
	{
		obj->reflection = -1;
		return (true);
	}
	obj->reflection = json_object_get_number(j_ob, "reflection");
	if (obj->reflection > 1)
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
