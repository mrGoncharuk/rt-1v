/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaniche <khaniche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 15:39:30 by khaniche          #+#    #+#             */
/*   Updated: 2019/09/14 20:08:46 by khaniche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	moves(t_vec vec_rot, t_vec orient)
{
	double	new[3];

	new[0] = vec_rot[0] * (cos(orient[1])) + vec_rot[2] * (sin(orient[1]));
	new[2] = -vec_rot[0] * (sin(orient[1])) + vec_rot[2] * (cos(orient[1]));
	vec_rot[0] = new[0];
	vec_rot[2] = new[2];
	new[1] = vec_rot[1] * (cos(orient[0])) + vec_rot[2] * (sin(orient[0]));
	new[2] = -vec_rot[1] * (sin(orient[0])) + vec_rot[2] * (cos(orient[0]));
	vec_rot[1] = new[1];
	vec_rot[2] = new[2];
	return (vec_rot);
}
