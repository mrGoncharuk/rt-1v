/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 15:23:19 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/23 21:03:55 by mhonchar         ###   ########.fr       */
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
# define RECURTION_DEPTH 3

typedef double			t_vec __attribute__((__ext_vector_type__(3)));

enum					e_obj_type {OBJ_SPHERE, OBJ_PLANE, OBJ_CONE, OBJ_CYL};
enum					e_light_type {LT_AMBIENT, LT_POINT, LT_DIRECT};

typedef struct			s_channel
{
	int					r;
	int					g;
	int					b;
}						t_channel;


typedef struct	s_ray
{
	t_vec				origin;
	t_vec				direction;
}						t_ray;


typedef struct			s_lights
{
	int					type;
	double				intensity;
	t_vec				position;
	t_vec				direction;
	t_channel			color;
	struct	s_lights	*next;
}						t_lights;




typedef struct			s_objects
{
	int					type;
	int					specular;
	double				reflection;
	t_vec				centre;
	t_vec				normal;
	t_vec				hit;
	t_channel			color;
	double				radius;

	struct	s_objects	*next;
}						t_objects;


typedef struct			s_intersect
{
	double				dist;
	t_objects			*closest_obj;
	t_vec				hit;
	t_vec				normal;


}						t_intersect;


typedef struct			s_rt
{
	t_objects			*objs;
	t_lights			*lights;
}						t_rt;


double					dot(t_vec a, t_vec b);
void					rt_intersect_ray_sphere(t_ray ray, t_objects *sphere, t_intersect *inter, double *dist_range);
Uint32					rt_channel_color_to_uint(t_channel color);
void					rt_mainloop(t_rt *rt, t_canvas *cn);
void					rt_load_objects(t_objects **objs, const char *fname);
void					rt_load_lights(t_lights **lights);
void					rt_intersect_ray(t_ray ray, t_objects *objs, t_intersect *inter, double *dist_range);
t_channel				rt_enlightenment(t_channel color, double intensity);
double					rt_compute_lighting(t_objects *objs, t_lights *lights, t_ray ray, t_intersect *inter);


#endif