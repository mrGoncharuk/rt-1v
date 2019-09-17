/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:46:34 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/17 15:01:26 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	parse_array_of_scene_objects(const JSON_Array *j_arr, t_rt *rt)
{
	JSON_Object	*j_ob;
	t_objects	*obj;
	size_t		size_i[2];

	size_i[0] = json_array_get_count(j_arr);
	obj = (t_objects *)malloc(sizeof(t_objects));
	rt->objs = obj;
	size_i[1] = 0;
	while (size_i[1] < size_i[0])
	{
		if (size_i[1] != 0)
		{
			obj->next = (t_objects *)malloc(sizeof(t_objects));
			obj = obj->next;
		}
		j_ob = json_array_get_object(j_arr, size_i[1]++);
		if (!pr_object(j_ob, obj))
		{
			obj->next = NULL;
			rt_clean(rt);
			return (false);
		}
	}
	obj->next = NULL;
	return (true);
}

bool	parse_array_of_lights(const JSON_Array *j_arr, t_rt *rt)
{
	JSON_Object	*j_ob;
	t_lights	*light;
	size_t		size_i[2];

	size_i[0] = json_array_get_count(j_arr);
	light = (t_lights *)malloc(sizeof(t_lights));
	rt->lights = light;
	size_i[1] = 0;
	while (size_i[1] < size_i[0])
	{
		if (size_i[1] != 0)
		{
			light->next = (t_lights *)malloc(sizeof(t_lights));
			light = light->next;
		}
		j_ob = json_array_get_object(j_arr, size_i[1]++);
		if (!pr_light(j_ob, light))
		{
			light->next = NULL;
			rt_clean(rt);
			return (false);
		}
	}
	light->next = NULL;
	return (true);
}

bool	rt_parse_objs_n_light(t_rt *rt, JSON_Object *json_objs)
{
	JSON_Array	*json_arr;

	if ((json_arr = json_object_get_array(json_objs, "objects")) == NULL)
	{
		ft_putstr("Error while getting array of scene objects\n");
		return (false);
	}
	if (!parse_array_of_scene_objects(json_arr, rt))
	{
		ft_putstr("Error while parsing objects");
		return (false);
	}
	if ((json_arr = json_object_get_array(json_objs, "lights")) == NULL)
	{
		ft_putstr("Error while getting array of lights\n");
		return (false);
	}
	if (!parse_array_of_lights(json_arr, rt))
	{
		ft_putstr("Error while parsing lights\n");
		return (false);
	}
	return (true);
}

bool	pr_all(t_rt *rt, JSON_Object *json_objs)
{
	if (!rt_parse_objs_n_light(rt, json_objs))
		return (false);
	if (!(pr_camera(json_objs, &(rt->camera))))
	{
		ft_putstr("Error while parsing camera");
		rt_clean(rt);
		return (false);
	}
	return (true);
}

bool	rt_parse_file(t_rt *rt, const char *fname)
{
	JSON_Value	*json_val;
	JSON_Object *json_objs;

	rt->objs = NULL;
	rt->lights = NULL;
	if ((json_val = json_parse_file(fname)) == NULL)
	{
		ft_putstr("Error while parsing json\n");
		return (false);
	}
	if ((json_objs = json_value_get_object(json_val)) == NULL)
	{
		ft_putstr("Error while getting object from value\n");
		return (false);
	}
	if (!pr_all(rt, json_objs))
	{
		json_object_clear(json_objs);
		json_value_free(json_val);
		rt_clean(rt);
		return (false);
	}
	json_object_clear(json_objs);
	json_value_free(json_val);
	return (true);
}
