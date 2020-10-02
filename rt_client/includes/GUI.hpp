#ifndef GUI_HPP
# define GUI_HPP

#include "imgui.h"

#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <list>
#include <atomic>
#include <mutex>

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif


#define PIXEL_BUFSIZE 500 * 500 * sizeof(uint32_t)
# define IMG_W 500
# define IMG_H 500
enum	e_effect_type
{
	EF_NONE,
	EF_NORMAL,
	EF_SEPIA,
	EF_WHITE,
	EF_GRAY,
	EF_CARTOON,
	EF_ALIASING
};

enum	e_keyid
{
	KEY_W = 26,
	KEY_S = 22,
	KEY_A = 4,
	KEY_D = 7,
	KEY_UP = 82,
	KEY_DOWN = 81,
	KEY_LEFT = 80,
	KEY_RIGHT = 79
};


typedef struct				s_view_flags
{
	bool					state_changed;
	bool					lmb_down;
	bool					aliasing;
}							t_view_flags;

typedef struct				s_move_flags
{
	bool					forward;
	bool					backward;
	bool					right;
	bool					left;
}							t_move_flags;



typedef struct				s_camera_rotation_flags
{
	bool					rot_x;
	bool					rot_y;
	bool					rot_x_min;
	bool					rot_y_min;
}							t_camera_rotation_flags;

typedef struct				s_raytrace_data
{
	char					header[16];
	unsigned int			size;
	t_view_flags			view_flags;
	int			effect_flags;
	t_move_flags			move_flags;
	t_camera_rotation_flags	cam_flags;
}							t_raytrace_data;



class GUI
{
private:
	SDL_Window			*window;
	SDL_GLContext		glContext;
	GLuint				rt_image_texture;
	ImVec4 				clearColor;
	bool				dataRecieved;
	t_raytrace_data		flags;
	t_raytrace_data		cache_flags;
	std::list<t_raytrace_data> buffer_list;
	const uint32_t			*shared_pixels;
	uint32_t			*pixels;
	GLuint 				my_image_texture;

public:
	GUI();
	~GUI();
	GUI(GUI const &);
	GUI &operator =(GUI const &);

	SDL_Window		*getWindow();
	SDL_GLContext	getGLContext();
	void			mainloop();
	void			events(std::atomic<bool>&, std::atomic<bool>&);
	void			update(std::mutex &recv_mutex);
	void			render();
	bool			stateChanged() const;
	t_raytrace_data	getFlags() const;
	void			setPixels(uint32_t *pxls);
	
};

#endif
