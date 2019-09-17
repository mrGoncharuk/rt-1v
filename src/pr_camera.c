/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 14:34:15 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/17 14:40:00 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	pr_camera(const JSON_Object *j_ob, t_camera *camera)
{
	JSON_Object	*j_cam;

	if ((j_cam = json_object_get_object(j_ob, "camera")) == NULL)
	{
		camera->orient = (t_vec) {0, 0, 0};
		camera->origin = (t_vec) {0, 0, 0};
	}
	else
	{
		if (!pr_vec_field(j_cam, "orient", &(camera->orient)))
			return (false);
		if (!pr_vec_field(j_cam, "origin", &(camera->origin)))
			return (false);
	}
	camera->orient[0] = DEG_TO_RAD(camera->orient[0]);
	camera->orient[1] = DEG_TO_RAD(camera->orient[1]);
	camera->orient[2] = DEG_TO_RAD(camera->orient[2]);
	return (true);
}
