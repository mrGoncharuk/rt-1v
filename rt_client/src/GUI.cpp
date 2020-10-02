#include "GUI.hpp"
#include <mutex>
#include <iostream>


#include <fstream>
#include <iostream>
using namespace std;

GUI::GUI(/* args */): clearColor(0.45f, 0.55f, 0.60f, 1.00f)
{
    // Setup SDL
    // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
    // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return ;
    }

    // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 Core + GLSL 150
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
   	window = SDL_CreateWindow("KardioGraph", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    glContext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glContext);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    bool err = gladLoadGL() == 0;
#else
    bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return ;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init(glsl_version);
    memset(&(this->flags), 0, sizeof(flags));
    pixels = new uint32_t[500*500];
}

GUI::~GUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    if (pixels)
        delete[] pixels;
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void    GUI::events(std::atomic<bool> &isRunning, std::atomic<bool> &imageLoaded)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            isRunning = false;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
            isRunning = false;
    }
    if (imageLoaded)
    {
        this->dataRecieved = true;
        imageLoaded = false;
    }
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
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 500, 500, 0, GL_RGBA , GL_UNSIGNED_INT_24_8, pixels);
    *out_texture = image_texture;
}


void	GUI::update(std::mutex &recv_mutex)
{
    // memset(&(this->flags), 0, sizeof(flags));
    bool show_demo_window = true;
    bool show_another_window = true;
    unsigned int flags = 0;
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
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

        ImGui::Text("Keys pressed:");
        for (int i = 0; i < buttonActionAmount; i++)
        if (ImGui::IsKeyPressed(buttons[i]))
        {
            ImGui::SameLine();
            ImGui::Text("%d (0x%X)", buttons[i], buttons[i]);
        }
        if (ImGui::IsKeyPressed(KEY_UP))
            this->flags.cam_flags.rot_y = true;
        else if (ImGui::IsKeyPressed(KEY_LEFT))
            this->flags.cam_flags.rot_x_min = true;
        else if (ImGui::IsKeyPressed(KEY_RIGHT))
            this->flags.cam_flags.rot_x = true;
        else if (ImGui::IsKeyPressed(KEY_DOWN))
            this->flags.cam_flags.rot_y_min = true;
        else if (ImGui::IsKeyPressed(KEY_W))
            this->flags.move_flags.forward = true;
        else if (ImGui::IsKeyPressed(KEY_S))
            this->flags.move_flags.backward = true;
        else if (ImGui::IsKeyPressed(KEY_D))
            this->flags.move_flags.right = true;
        else if (ImGui::IsKeyPressed(KEY_A))
            this->flags.move_flags.left = true;
        ImGui::End();
    }


    if (this->dataRecieved)
    {
        {
            std::lock_guard<std::mutex> lock(recv_mutex);
            memcpy(this->pixels, this->shared_pixels, sizeof(Uint32) * 500 * 500);
        }
        // for (int i = 0; i < 500 * 500 * 4; i++)
        //     std::cout << this->pixels[i] << " "; 
        LoadTextureFromArray(this->pixels, &this->my_image_texture);
        this->dataRecieved = false;
        // {
        //     std::ofstream myfile ("example.txt");
        //     if (myfile.is_open())
        //     {
        //         for(int count = 0; count < 500*500; count ++)
        //         {
        //             myfile << this->pixels[count] << " " ;
        //         }
        //         myfile.close();
        //     }
        //     else cout << "Unable to open file";
        //     // return 0;
        // }
    }

    {
        ImGui::Begin("OpenGL Texture Text");
        ImGui::Text("pointer = %p", this->my_image_texture);
        ImGui::Text("size = %d x %d", 500, 500);
        ImGui::Image((void*)(intptr_t)this->my_image_texture, ImVec2(500, 500));
        ImGui::End();
    }
    // ImGui::NewFrame();
    // ImGui::CheckboxFlags("Sepia", &flags, 0);
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
	ImGui::Render();
	ImGuiIO& io = ImGui::GetIO();
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(window);

    
}

SDL_Window *GUI::getWindow() { return (this->window); }
SDL_GLContext	GUI::getGLContext() { return (this->glContext); }
t_raytrace_data	GUI::getFlags() const { return this->flags; }
void			GUI::setPixels(uint32_t *shared_pxls) { this->shared_pixels = shared_pxls; };
// void	GUI::setStatus(std::atomic<bool> &status) { this->running = status; };
