/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 15:23:19 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/20 18:01:11 by mhonchar         ###   ########.fr       */
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
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

# define THREADS_AMOUNT 6
# define M_P 3.14159265358979323846
# define CW WIN_WIDTH
# define CH WIN_HEIGHT
# define VIEWPORT_WIDTH 1
# define VIEWPORT_HEIGHT 1
# define DIST_CAM_PP 1
# define RECURTION_DEPTH 9
# define ROT_POWER 0.0872664626;
# define TEXTURES_COUNT 7
# define DISRUPT 6

typedef double			t_vec __attribute__((__ext_vector_type__(3)));

enum					e_obj_type {OBJ_SPHERE, OBJ_PLANE, OBJ_CONE, OBJ_CYL,
	OBJ_PAR};
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
	int					texture;
	int					compose;
	int					negative;
	double				specular;
	double				reflection;
	double				transparency;
	t_vec				centre;
	t_vec				cut;
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
	t_objects			*transp_obj;
}						t_intersect;

typedef struct			s_camera
{
	t_vec				origin;
	t_vec				orient;
}						t_camera;

typedef struct			s_rt
{
	SDL_Surface			*texture[TEXTURES_COUNT];	// surfaces
	t_objects			*objs;			// objects 
	t_lights			*lights;		// light sources 
	t_camera			camera;			// camera position
	Uint32				*pixels;		// image

	// thread_data
	int					x_start;
	int					x_end;
}						t_rt;

typedef struct			s_flags
{
	bool				running;
	bool				state_changed;
	bool				rot_x;
	bool				rot_y;
	bool				rot_x_min;
	bool				rot_y_min;
	bool				forward;
	bool				backward;
	bool				right;
	bool				left;
	bool				lmb_down;
	bool				sepia;
	bool				white;
	bool				gray;
	bool				clear;
	bool				cartoon;
	bool				aliasing;
}						t_flags;

typedef struct			s_sdls
{
	t_canvas			canvas;
	t_flags				flags;
	SDL_Event			event;
	const char			*fname;
}						t_sdls;

typedef struct			s_color_trace
{
	t_channel			local_color;
	t_channel			color_texture;
	t_channel			reflected_color;
	t_channel			transparency_color;
}						t_color_trace;

typedef struct			s_shadow_st
{
	double				dist_range[2];
	t_intersect			inter;
	t_ray				ray;
	t_objects			*obstacle_obj;
	double				obstacle_dist;
	t_objects			*transp_obj;
	double				transp_dist;
}						t_sh;

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
void					rt_intersect_ray_par(t_ray ray, t_objects *par,
							t_intersect *inter, double *dist_range);
void					rt_intersect_ray_cone(t_ray ray, t_objects *cone,
							t_intersect *inter, double *dist_range);
t_vec					rt_calc_plane_normal(t_intersect *inter, t_ray ray);
t_vec					rt_calc_cone_normal(t_intersect *i, t_ray ray);
t_vec					rt_calc_sphere_normal(t_intersect *inter);
t_vec					rt_calc_cylinder_normal(t_intersect *inter, t_ray ray);
t_vec					rt_calc_par_normal(t_intersect *inter, t_ray ray);
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

t_channel				rt_calc_ref_tran_color(t_color_trace color, double r,
							double t);
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
bool					pr_obj_par(const JSON_Object *j_ob, t_objects *par);
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
bool					pr_transparency(const JSON_Object *j_ob,
						t_objects *obj);
bool					pr_cut(const JSON_Object *j_ob, t_objects *obj);
bool					pr_texture(const JSON_Object *j_ob, t_objects *obj);
bool					pr_compose(const JSON_Object *j_ob, t_objects *obj);
bool					pr_radius_pl(const JSON_Object *j_ob, t_objects *obj);
bool					pr_negative(const JSON_Object *j_ob, t_objects *obj);
bool					check_reflect_transparency(t_objects *obj);
void					check_light(t_lights **lg);

void					*rt_threaded_loop(void *r);
void					rt_thread_tracer(t_rt *rt);
t_vec					rt_rotate_camera(t_camera *camera, t_vec ray_dir);
void					ft_event(t_sdls *app);
void					ft_update(t_sdls *app, t_rt *rt);
t_vec					moves(t_vec vec_rot, t_vec orient);
void					ft_event_(t_sdls *app);
bool					false_error(char *str);
void					compose_obj(t_objects **obj);
void					rt_cut_figure(t_intersect *inter, double *data,
							t_objects *obj, t_ray ray);
void					rt_sort_roots(double *roots, double *dist_range);

t_channel				texture_mapping(t_rt *rtv, t_vec p, t_objects *ob);
bool					load_textures(t_rt *rtv);
bool					rt_find_closest_obj(t_ray ray, t_objects *objs,
						t_intersect *inter, double *dist_range);
t_vec					normalize(t_vec vec);

t_channel				noise_text(t_vec p, t_vec center);
t_channel				wave_chechboard(t_vec p);
void					sepia_image(Uint32 *pixels, Uint32 *pixels_copy);
void					save_image(const char *file_name,
							SDL_Renderer *renderer);
void					anti_aliasing(Uint32 *pixels, int intensive);

double					deg_to_rad(double angle);
t_channel				disruption_1(t_vec p, t_vec center);
t_channel				disruption_2(t_vec p, t_vec center);
t_channel				disruption_3(t_vec p, t_vec center);
t_channel				disruption_4(t_vec p, t_vec center);
void					cartoon(Uint32 *pixels, Uint32 *pixels_copy);
void					gray_rad(Uint32 *pixels, Uint32 *pixels_copy);
void					white_rad(Uint32 *pixels, Uint32 *pixels_copy);
void					neg_obj(t_objects **obj);
t_objects				*rt_point_in_shadow(t_objects *objs, t_vec point,
							t_vec light, t_lights l);

#endif
