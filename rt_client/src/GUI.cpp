#include "GUI.hpp"
#include <mutex>
#include <iostream>


#include <fstream>
#include <iostream>
using namespace std;

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

std::vector<int> generateKeys()
{
    std::vector<int>    inputKeys{
                        GLFW_KEY_W,
                        GLFW_KEY_A,
                        GLFW_KEY_S,
                        GLFW_KEY_D,
                        GLFW_KEY_RIGHT,
                        GLFW_KEY_LEFT,
                        GLFW_KEY_UP,
                        GLFW_KEY_DOWN,
                        GLFW_KEY_ESCAPE
    };
    return inputKeys;
}

GUI::GUI(/* args */): clearColor(0.45f, 0.55f, 0.60f, 1.00f), keyboardInput(generateKeys())
{
    memset(&(this->flags), 0, sizeof(flags));
    pixels = new uint32_t[500*500];
}

bool    GUI::InitGraphics()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        std:cerr << "Error while glfwIinit()" << std::endl;
        return false;
    }

    // Decide GL+GLSL versions
    #ifdef __APPLE__
        // GL 3.2 + GLSL 150
        const char* glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
    #else
        // GL 3.0 + GLSL 130
        const char* glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
    #endif

    // Create window with graphics context
    this->window = glfwCreateWindow(1280, 720, "RT-Online", NULL, NULL);
    if (this->window == NULL)
    {
        std::cerr << "Error while initializing glfw window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
    #if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
        bool err = gl3wInit() != 0;
    #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
        bool err = glewInit() != GLEW_OK;
    #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
        bool err = gladLoadGL() == 0;
    #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
        bool err = gladLoadGL(glfwGetProcAddress) == 0; // glad2 recommend using the windowing library loader instead of the (optionally) bundled one.
    #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
        bool err = false;
        glbinding::Binding::initialize();
    #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
        bool err = false;
        glbinding::initialize([](const char* name) { return (glbinding::ProcAddress)glfwGetProcAddress(name); });
    #else
        bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
    #endif
    if (err)
    {
        glfwTerminate();
        glfwDestroyWindow(window);
        std::cerr << "Failed to initialize OpenGL loader!" << std::endl;
        return false;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    keyboardInput.setupKeyInputs(this->window);
    return true;
}

GUI::~GUI()
{
    delete[] pixels;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}


void    GUI::events(std::atomic<bool> &isRunning, std::atomic<bool> &imageLoaded)
{
    glfwPollEvents();
    if (glfwWindowShouldClose(this->window))
        isRunning = false;
    if (imageLoaded)
    {
        this->dataRecieved = true;
        imageLoaded = false;
    }
    if (keyboardInput.getIsKeyDown(GLFW_KEY_UP))
    {
        this->flags.cam_flags.rot_y = true;
        std::cout << "KEKEKE 1" << std::endl;
    }
    else if (ImGui::IsKeyPressed(KEY_LEFT))
        this->flags.cam_flags.rot_x_min = true;
    else if (ImGui::IsKeyPressed(KEY_RIGHT))
        this->flags.cam_flags.rot_x = true;
    else if (ImGui::IsKeyPressed(KEY_DOWN))
        this->flags.cam_flags.rot_y_min = true;
    else if (keyboardInput.getIsKeyDown(GLFW_KEY_W))
    {
        this->flags.move_flags.forward = true;
        std::cout << "KEKEKE 2" << std::endl;
    }
    else if (ImGui::IsKeyPressed(KEY_S))
        this->flags.move_flags.backward = true;
    else if (ImGui::IsKeyPressed(KEY_D))
        this->flags.move_flags.right = true;
    else if (ImGui::IsKeyPressed(KEY_A))
        this->flags.move_flags.left = true;
}

void LoadTextureFromArray(uint32_t *pixels, GLuint* out_texture)
{
    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    // glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);s
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 500, 500, 0, GL_RGBA , GL_UNSIGNED_BYTE, pixels);
    *out_texture = image_texture;
}


void	GUI::update(std::mutex &recv_mutex)
{
    // memset(&(this->flags), 0, sizeof(flags));
    bool show_demo_window = true;
    bool show_another_window = true;
    unsigned int flags = 0;
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        const int buttonActionAmount = 8;
        int buttons[buttonActionAmount] = {26 , 22, 4, 7, 82, 81, 80, 79};

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::RadioButton("Normal Effect", &(this->flags.effect_flags), EF_NORMAL);
        ImGui::RadioButton("Sepia effect", &(this->flags.effect_flags), EF_SEPIA);
        ImGui::RadioButton("Negative effect", &(this->flags.effect_flags), EF_WHITE);
        ImGui::RadioButton("Grey scale effect", &(this->flags.effect_flags), EF_GRAY);
        ImGui::RadioButton("Cartoon effect", &(this->flags.effect_flags), EF_CARTOON);
        ImGui::Checkbox("Anti-Aliasing effect", &(this->flags.view_flags.aliasing));

        ImGui::End();
    }


    if (this->dataRecieved)
    {
        {
            std::lock_guard<std::mutex> lock(recv_mutex);
            memcpy(this->pixels, this->shared_pixels, sizeof(uint32_t) * 500 * 500);
        }
        LoadTextureFromArray(this->pixels, &this->my_image_texture);
        this->dataRecieved = false;
    }

    {
        ImGui::Begin("OpenGL Texture Text");
        ImGui::Text("pointer = %p", this->my_image_texture);
        ImGui::Text("size = %d x %d", 500, 500);
        ImGui::Image((void*)(intptr_t)this->my_image_texture, ImVec2(500, 500));
        ImGui::End();
    }
}

bool    GUI::stateChanged() const
{
    // if current flags != cached flags
    if (!(memcmp(&(this->flags), &(this->cache_flags), sizeof(t_raytrace_data)) == 0))
    {
        
        memcpy((void *)&(this->cache_flags), &(this->flags), sizeof(t_raytrace_data));
        return true;
    }
    return false;
}


void	GUI::render()
{
	// ImGui::Render();
	// ImGuiIO& io = ImGui::GetIO();
	// glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	// glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
	// glClear(GL_COLOR_BUFFER_BIT);
	// ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// SDL_GL_SwapWindow(window);


    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);


}

GLFWwindow *GUI::getWindow() { return (this->window); }

t_raytrace_data	GUI::getFlags() const { return this->flags; }
void			GUI::setPixels(uint32_t *shared_pxls) { this->shared_pixels = shared_pxls; };
// void	GUI::setStatus(std::atomic<bool> &status) { this->running = status; };
