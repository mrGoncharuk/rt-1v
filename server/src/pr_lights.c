/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_lights.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 13:19:29 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/10 18:05:33 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	pr_light_ambient(const JSON_Object *j_ob, t_lights *ambient)
{
	if (!pr_light_intensity(j_ob, ambient))
		return (false);
	return (true);
}

bool	pr_light_point(const JSON_Object *j_ob, t_lights *point)
{
	if (!pr_light_intensity(j_ob, point) ||
		!pr_vec_field(j_ob, "position", &(point->position)))
		return (false);
	return (true);
}

bool	pr_light_direct(const JSON_Object *j_ob, t_lights *direct)
{
	if (!pr_light_intensity(j_ob, direct) ||
		!pr_vec_field(j_ob, "direction", &(direct->direction)))
		return (false);
	return (true);
}
