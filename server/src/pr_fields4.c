/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_fields4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 10:41:47 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/09/20 13:48:33 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	check_light(t_lights **lg)
{
	t_lights	*lig;
	bool		ambient;

	ambient = false;
	lig = *lg;
	while (lig->next)
	{
		if (lig->type == LT_AMBIENT)
			ambient = true;
		lig = lig->next;
	}
	if (ambient == false)
	{
		lig->next = (t_lights *)malloc(sizeof(t_lights));
		lig = lig->next;
		lig->type = LT_AMBIENT;
		lig->intensity = 0.1;
		lig->next = NULL;
	}
}

bool	pr_radius_pl(const JSON_Object *j_ob, t_objects *obj)
{
	if (!json_object_has_value_of_type(j_ob, "radius", JSONNumber))
		obj->radius = -1;
	obj->radius = json_object_get_number(j_ob, "radius");
	return (true);
}

bool	pr_negative(const JSON_Object *j_ob, t_objects *obj)
{
	if (!json_object_has_value_of_type(j_ob, "negative", JSONNumber))
	{
		obj->negative = -1;
		return (true);
	}
	obj->negative = 1;
	return (true);
}
