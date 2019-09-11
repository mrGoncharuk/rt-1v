/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rotation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 19:51:00 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/11 18:01:51 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_init_rot_matrix(t_camera *cam)
{
	cam->rot_x[0][0] = 1;
	cam->rot_x[0][1] = 0;
	cam->rot_x[0][2] = 0;
	cam->rot_x[1][0] = 0;
	cam->rot_x[2][0] = 0;
	rt_recalc_x_mtrx(cam->rot_x, cam->orient[0]);
	cam->rot_y[0][1] = 0;
	cam->rot_y[1][0] = 0;
	cam->rot_y[1][1] = 1;
	cam->rot_y[1][2] = 0;
	cam->rot_y[2][1] = 0;
	rt_recalc_y_mtrx(cam->rot_y, cam->orient[1]);
	cam->rot_z[0][2] = 0;
	cam->rot_z[1][2] = 0;
	cam->rot_z[2][0] = 0;
	cam->rot_z[2][1] = 0;
	cam->rot_z[2][2] = 1;
	rt_recalc_z_mtrx(cam->rot_z, cam->orient[2]);
}

t_vec	rt_rotate_camera(t_camera *camera, t_vec ray_dir)
{
	t_vec	res;
	t_vec	tmp;

	tmp = ray_dir;
	res[0] = tmp[0];
	res[1] = tmp[1] * cos(camera->orient[0]) + tmp[2] * sin(camera->orient[0]);
	res[2] = -tmp[1] * sin(camera->orient[0]) + tmp[2] * cos(camera->orient[0]);
	return (res);
}

void	rt_recalc_x_mtrx(double mtrx[3][3], double rad)
{
	mtrx[1][1] = cos(rad);
	mtrx[1][2] = -sin(rad);
	mtrx[2][1] = sin(rad);
	mtrx[2][2] = cos(rad);
}

void	rt_recalc_y_mtrx(double mtrx[3][3], double rad)
{
	mtrx[0][0] = cos(rad);
	mtrx[0][2] = sin(rad);
	mtrx[2][0] = -sin(rad);
	mtrx[2][2] = cos(rad);
}

void	rt_recalc_z_mtrx(double mtrx[3][3], double rad)
{
	mtrx[0][0] = cos(rad);
	mtrx[0][1] = -sin(rad);
	mtrx[1][0] = sin(rad);
	mtrx[1][1] = cos(rad);
}
