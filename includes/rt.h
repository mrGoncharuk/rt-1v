/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 15:23:19 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/21 19:06:31 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <float.h>


# include "guimp.h"
# define CW CN_WIDTH
# define CH CN_HEIGHT
# define VIEWPORT_WIDTH 1
# define VIEWPORT_HEIGHT 1
# define DIST_CAM_PP 1
typedef double	t_vec __attribute__((__ext_vector_type__(3)));

enum	e_obj_type {OBJ_SPHERE, OBJ_PLANE, OBJ_CONE, OBJ_CYL};

typedef struct	s_channel
{
	int			r;
	int			g;
	int			b;
}				t_channel;


typedef struct	s_ray
{
	t_vec		origin;
	t_vec		direction;
}				t_ray;


typedef struct	s_objects t_objects;
typedef struct	s_objects
{
	int			type;
	double		radius;
	t_vec		centre;
	t_channel	color;
	t_objects	*next;
}				t_objects;


typedef struct	s_rt
{
	t_objects	*objs;
}				t_rt;


double	dot(t_vec a, t_vec b);
t_vec	rt_intersect_ray_sphere(t_ray ray, t_objects *objs);
Uint32	rt_channel_color_to_uint(t_channel color);
void	rt_mainloop(t_rt *rt, t_canvas *cn);
void	rt_load_objects(t_objects **objs, const char *fname);
#endif