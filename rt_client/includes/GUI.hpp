#ifndef GUI_HPP
# define GUI_HPP

#include "imgui.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <list>
#include <atomic>
#include <mutex>


// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>            // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>            // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>          // Initialize with gladLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
#include <glad/gl.h>            // Initialize with gladLoadGL(...) or gladLoaderLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/Binding.h>  // Initialize with glbinding::Binding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/glbinding.h>// Initialize with glbinding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
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
	GLFWwindow			*window;
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

	GLFWwindow		*getWindow();

	void			mainloop();
	void			events(std::atomic<bool>&, std::atomic<bool>&);
	void			update(std::mutex &recv_mutex);
	void			render();
	bool			stateChanged() const;
	t_raytrace_data	getFlags() const;
	void			setPixels(uint32_t *pxls);
	
};

#endif
