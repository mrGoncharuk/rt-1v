/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_compose_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 16:18:52 by khaniche          #+#    #+#             */
/*   Updated: 2019/09/20 17:39:29 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		copy_negative(t_objects *ob, t_objects *copy)
{
	copy->type = ob->type;
	copy->texture = -1;
	copy->compose = -1;
	copy->specular = ob->specular;
	copy->reflection = 0;
	copy->transparency = 1;
	copy->centre = ob->centre;
	copy->cut = ob->cut;
	copy->orient = ob->orient;
	copy->color = ob->color;
	if (ob->radius > 2)
		copy->radius = ob->radius / 2;
	else
		copy->radius = 1.5;
	copy->k = ob->k;
	copy->angle = ob->angle;
}

static void		copy_(t_objects *ob, t_objects *copy)
{
	static int	i;

	copy->specular = ob->specular;
	copy->color = ob->color;
	if (i == 0)
	{
		copy->centre = ob->centre;
		copy->centre.y += ob->radius * 1.2;
	}
	else
	{
		copy->centre = ob->centre;
		copy->centre.y -= ob->radius * 2;
	}
	copy->color = ob->color;
	copy->orient = ob->orient;
	if (i == 0)
		copy->radius = ob->radius - ob->radius * 0.6;
	else
		copy->radius = ob->radius + ob->radius * 0.6;
	copy->reflection = ob->reflection;
	copy->texture = ob->texture;
	copy->transparency = ob->transparency;
	i++;
}

static	void	spec(t_objects **obj, t_objects *ob, t_objects *t_ob)
{
	*obj = ob;
	ob->specular = 50;
	ob->next->specular = 0;
	t_ob->specular = 0;
}

void			compose_obj(t_objects **obj)
{
	t_objects	*ob;
	t_objects	*t_ob;
	bool		compose;

	compose = false;
	t_ob = *obj;
	while (t_ob)
	{
		if (t_ob->compose == 0 && t_ob->type == OBJ_SPHERE)
		{
			compose = true;
			break ;
		}
		t_ob = t_ob->next;
	}
	if (compose == true)
	{
		ob = (t_objects *)malloc(sizeof(t_objects));
		ob->next = (t_objects *)malloc(sizeof(t_objects));
		ob->next->next = NULL;
		copy_(t_ob, ob);
		copy_(t_ob, ob->next);
		ob->next->next = *obj;
		spec(obj, ob, t_ob);
	}
}

void			neg_obj(t_objects **obj)
{
	t_objects	*ob;
	t_objects	*t_ob;
	bool		negative;

	negative = false;
	t_ob = *obj;
	while (t_ob)
	{
		if (t_ob->negative == 1 && t_ob->type == OBJ_PLANE)
		{
			negative = true;
			break ;
		}
		t_ob = t_ob->next;
	}
	if (negative == true)
	{
		ob = (t_objects *)malloc(sizeof(t_objects));
		ob->next = NULL;
		copy_negative(t_ob, ob);
		ob->next = *obj;
		*obj = ob;
	}
	compose_obj(obj);
}
