/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 15:23:19 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/12 21:07:30 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <float.h>
# include <stdbool.h>
# include <pthread.h>
# include "libft.h"
# include "canvas.h"
# include "window.h"
# include "error_handler.h"
# include "parson.h"
# include "SDL2/SDL.h"
# include "SDL2_image/SDL_image.h"

# define THREADS_AMOUNT 4
# define CW CN_WIDTH
# define CH CN_HEIGHT
# define VIEWPORT_WIDTH 1
# define VIEWPORT_HEIGHT 1
# define DIST_CAM_PP 1
# define RECURTION_DEPTH 3
# define DEG_TO_RAD(angle) (M_PI * angle) / 180
# define ROT_POWER DEG_TO_RAD(15);

typedef double			t_vec __attribute__((__ext_vector_type__(3)));

enum					e_obj_type {OBJ_SPHERE, OBJ_PLANE, OBJ_CONE, OBJ_CYL};
enum					e_light_type {LT_AMBIENT, LT_POINT, LT_DIRECT};

typedef struct			s_channel
{
	int					r;
	int					g;
	int					b;
}						t_channel;

typedef struct			s_ray
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
	struct s_lights		*next;
}						t_lights;

typedef struct			s_objects
{
	int					type;
	double				specular;
	double				reflection;
	t_vec				centre;
	t_vec				orient;
	t_channel			color;
	double				radius;
	double				k;
	double				angle;
	struct s_objects	*next;
}						t_objects;

typedef struct			s_intersect
{
	double				dist;
	t_objects			*closest_obj;
	t_vec				hit;
	t_vec				normal;
}						t_intersect;

typedef struct			s_camera
{
	t_vec				origin;
	t_vec				orient;
	double				rot_x[3][3];
	double				rot_y[3][3];
	double				rot_z[3][3];
}						t_camera;

typedef struct			s_rt
{
	t_objects			*objs;
	t_lights			*lights;
	t_camera			camera;
	Uint32				*pixels;
	int					x_start;
	int					x_end;
}						t_rt;

typedef struct			s_flags
{
	bool				running;
	bool				lmb_down;
	bool				clear_canvas;
	bool				state_changed;
	bool				rot_x;
	bool				rot_y;
	bool				rot_z;
}						t_flags;

typedef struct			s_sdls
{
	t_canvas			canvas;
	t_flags				flags;
}						t_sdls;

void					ft_sdl_init(t_sdls *app);
void					ft_sdl_clean(t_sdls *app);
void					ft_mainloop(t_sdls *app);

double					dot(t_vec a, t_vec b);
void					rt_intersect_ray_sphere(t_ray ray, t_objects *sphere,
							t_intersect *inter, double *dist_range);
void					rt_intersect_ray_plane(t_ray ray, t_objects *plane,
							t_intersect *inter, double *dist_range);
void					rt_intersect_ray_cylinder(t_ray ray, t_objects *cyl,
							t_intersect *inter, double *dist_range);
void					rt_intersect_ray_cone(t_ray ray, t_objects *cone,
							t_intersect *inter, double *dist_range);
t_vec					rt_calc_plane_normal(t_intersect *inter, t_ray ray);
t_vec					rt_calc_sphere_normal(t_intersect *inter);
t_vec					rt_calc_cylinder_normal(t_intersect *inter, t_ray ray);
t_vec					rt_calc_cone_normal(t_intersect *inter, t_ray ray);
Uint32					rt_channel_color_to_uint(t_channel color);
void					rt_mainloop(t_rt *rt, Uint32 *pixels);
t_channel				rt_trace_ray(t_ray ray, t_rt *rt, double *dist_range,
									int depth);
void					rt_intersect_ray(t_ray ray, t_objects *objs,
							t_intersect *inter, double *dist_range);
double					rt_select_dist(double *roots, double *dist_range);
t_channel				rt_enlightenment(t_channel color, double intensity);
t_vec					rt_canvas_to_viewport(int x, int y);
double					rt_compute_lighting(t_objects *objs,
							t_lights *lights, t_ray ray, t_intersect *inter);
t_channel				rt_calc_reflected_color(t_channel local_color,
							t_channel reflected_color, double r);
t_vec					rt_reflect_ray(t_vec normal, t_vec ray_dir);
t_vec					rt_calc_normal(t_intersect *inter, t_ray ray);
double					vec_length(t_vec v);
void					rt_clean(t_rt *rt);
void					rt_free_lights(t_lights **lights);
void					rt_free_objects(t_objects **objs);

bool					rt_parse_file(t_rt *rt, const char *fname);
bool					pr_object(const JSON_Object *j_ob, t_objects *obj);
bool					pr_obj_cone(const JSON_Object *j_ob, t_objects *cone);
bool					pr_obj_cyl(const JSON_Object *j_ob, t_objects *cyl);
bool					pr_obj_plane(const JSON_Object *j_ob, t_objects *plane);
bool					pr_obj_sphere(const JSON_Object *j_ob,
										t_objects *sphere);
bool					pr_light(const JSON_Object *j_ob, t_lights *light);
bool					pr_light_direct(const JSON_Object *j_ob,
										t_lights *direct);
bool					pr_light_point(const JSON_Object *j_ob,
										t_lights *point);
bool					pr_light_ambient(const JSON_Object *j_ob,
										t_lights *ambient);
bool					pr_angle(const JSON_Object *j_ob, t_objects *obj);
bool					pr_light_intensity(const JSON_Object *j_ob,
											t_lights *light);
bool					pr_vec_field(const JSON_Object *j_ob,
									const char *field_name, t_vec *vec);
bool					pr_channel_color(const JSON_Object *j_ob, t_objects *o);
bool					pr_specular(const JSON_Object *j_ob, t_objects *obj);
bool					pr_reflection(const JSON_Object *j_ob, t_objects *obj);
bool					pr_radius(const JSON_Object *j_ob, t_objects *obj);

t_vec					rt_rotate_camera(t_camera *camera, t_vec ray_dir);
void					*rt_threaded_loop(void *r);
void					rt_thread_tracer(t_rt *rt);

#endif
