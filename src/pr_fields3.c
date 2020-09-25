/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_fields3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 21:23:35 by khaniche          #+#    #+#             */
/*   Updated: 2019/09/19 16:58:18 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	pr_texture(const JSON_Object *j_ob, t_objects *obj)
{
	if (!json_object_has_value_of_type(j_ob, "texture", JSONNumber))
	{
		obj->texture = -1;
		return (true);
	}
	obj->texture = json_object_get_number(j_ob, "texture");
	return (true);
}

bool	pr_transparency(const JSON_Object *j_ob, t_objects *obj)
{
	if (!json_object_has_value_of_type(j_ob, "transparency", JSONNumber))
	{
		obj->transparency = -1;
		return (true);
	}
	obj->transparency = json_object_get_number(j_ob, "transparency");
	if (obj->transparency > 1)
		return (false_error("transparency > 1"));
	return (true);
}

bool	pr_compose(const JSON_Object *j_ob, t_objects *obj)
{
	if (!json_object_has_value_of_type(j_ob, "compose", JSONNumber))
	{
		obj->compose = -1;
		return (true);
	}
	obj->compose = json_object_get_number(j_ob, "compose");
	return (true);
}

bool	pr_cut(const JSON_Object *j_ob, t_objects *obj)
{
	if (json_object_has_value_of_type(j_ob, "cut", JSONArray) == false)
	{
		obj->cut[2] = 0;
		obj->cut[0] = -2147483648;
		obj->cut[1] = 2147483647;
		return (true);
	}
	if (pr_vec_field(j_ob, "cut", &(obj->cut)) == false)
		return (false);
	if (obj->cut[1] <= obj->cut[0])
		return (false);
	return (true);
}

bool	check_reflect_transparency(t_objects *obj)
{
	if (obj->reflection >= 0.5 && obj->transparency >= 0.5)
		return (false_error("Change your reflection or transparency"));
	return (true);
}
