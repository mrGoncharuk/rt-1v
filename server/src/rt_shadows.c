/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_shadows.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 15:22:18 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/09/20 15:22:58 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double		shadow(t_objects **obstacle_obj, t_intersect *inter,
					double obstacle_dist)
{
	if (*obstacle_obj)
	{
		if (obstacle_dist < inter->dist)
		{
			*obstacle_obj = inter->closest_obj;
			return (inter->dist);
		}
	}
	else
	{
		*obstacle_obj = inter->closest_obj;
		return (inter->dist);
	}
	return (inter->dist);
}

static t_objects	*shadow_dop(t_sh *sh)
{
	if (sh->transp_obj)
	{
		if (sh->obstacle_obj != NULL && sh->obstacle_dist > sh->transp_dist)
			return (sh->obstacle_obj);
		else if (sh->transp_dist < sh->obstacle_dist)
			return (sh->transp_obj);
	}
	return (sh->obstacle_obj);
}

static void			init_shadow(t_sh *sh)
{
	sh->obstacle_dist = DBL_MAX;
	sh->obstacle_obj = NULL;
	sh->transp_dist = DBL_MAX;
	sh->transp_obj = NULL;
	sh->dist_range[0] = 0.0001;
}

t_objects			*rt_point_in_shadow(t_objects *objs, t_vec point,
						t_vec light, t_lights l)
{
	t_sh	sh;

	init_shadow(&sh);
	sh.ray.origin = point;
	sh.ray.direction = light;
	sh.dist_range[1] = (l.type == LT_POINT) ?
	vec_length(point - l.position) : DBL_MAX;
	while (objs)
	{
		sh.inter.dist = DBL_MAX;
		sh.inter.closest_obj = NULL;
		rt_intersect_ray(sh.ray, objs, &sh.inter, sh.dist_range);
		if (sh.inter.closest_obj)
		{
			if (sh.inter.closest_obj->transparency < 0)
				sh.obstacle_dist = shadow(&sh.obstacle_obj,
				&sh.inter, sh.obstacle_dist);
			if (sh.inter.closest_obj->transparency > 0)
				sh.transp_dist = shadow(&sh.transp_obj,
				&sh.inter, sh.transp_dist);
		}
		objs = objs->next;
	}
	return (shadow_dop(&sh));
}
