/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 15:26:59 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/28 16:52:46 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_clean(t_rt *rt)
{
	rt_free_objects(&(rt->objs));
	rt_free_lights(&(rt->lights));
}

void	rt_free_lights(t_lights **lig)
{
	t_lights	*l;
	t_lights	*lights;

	lights = *lig;
	while (lights != NULL)
	{
		l = lights->next;
		free(lights);
		lights = l;
	}
	*lig = NULL;
}

void	rt_free_objects(t_objects **ob)
{
	t_objects	*o;
	t_objects	*objs;

	objs = *ob;
	while (objs != NULL)
	{
		o = objs->next;
		free(objs);
		objs = o;
	}
	*ob = NULL;
}
