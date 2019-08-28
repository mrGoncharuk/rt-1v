/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:46:34 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/28 16:49:35 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	parse_array_of_scene_objects(const JSON_Array *j_arr, t_objects **objs)
{
	JSON_Object	*j_ob;
	t_objects	*obj;
	size_t		size;
	size_t		i;

	size = json_array_get_count(j_arr);
	i = 0;
	obj = (t_objects *)malloc(sizeof(t_objects));
	*objs = obj;
	while (i < size)
	{
		if (i != 0)
		{
			obj->next = (t_objects *)malloc(sizeof(t_objects));
			obj = obj->next;
		}
		j_ob = json_array_get_object(j_arr, i++);
		if (!pr_object(j_ob, obj))
		{
			rt_free_objects(objs);
			return (false);
		}
	}
	obj->next = NULL;
	return (true);
}

bool	parse_array_of_lights(const JSON_Array *j_arr, t_lights **lights)
{
	JSON_Object	*j_ob;
	t_lights	*light;
	size_t		size;
	size_t		i;

	size = json_array_get_count(j_arr);
	i = 0;
	light = (t_lights *)malloc(sizeof(t_lights));
	*lights = light;
	while (i < size)
	{
		if (i != 0)
		{
			light->next = (t_lights *)malloc(sizeof(t_lights));
			light = light->next;
		}
		j_ob = json_array_get_object(j_arr, i++);
		if (!pr_light(j_ob, light))
		{
			rt_free_lights(lights);
			return (false);
		}
	}
	light->next = NULL;
	return (true);
}

bool	rt_parse_file(t_rt *rt, const char *fname)
{
	JSON_Value	*json_val;
	JSON_Object *json_objs;
	JSON_Array	*json_arr;

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
	if ((json_arr = json_object_get_array(json_objs, "objects")) == NULL)
	{
		ft_putstr("Error while getting array of scene objects\n");
		return (false);
	}
	if (!parse_array_of_scene_objects(json_arr, &(rt->objs)))
	{
		ft_putstr("Error while parsing objects");
		return (false);
	}
	if ((json_arr = json_object_get_array(json_objs, "lights")) == NULL)
	{
		ft_putstr("Error while getting array of lights\n");
		return (false);
	}
	if (!parse_array_of_lights(json_arr, &(rt->lights)))
	{
		ft_putstr("Error while parsing objects");
		return (false);
	}
	ft_putstr("All good so far\n");
	//json_value_free(json_val);
	return (true);
}
