#
# Cross Platform Makefile
# Compatible with MSYS2/MINGW, Ubuntu 14.04.1 and Mac OS X
#
# You will need SDL2 (http://www.libsdl.org):
# Linux:
#   apt-get install libsdl2-dev
# Mac OS X:
#   brew install sdl2
# MSYS2:
#   pacman -S mingw-w64-i686-SDL
#

CXX = g++ -std=c++11
# CXX = clang++ -std=c++11

IMPL_DIR = imgui/examples/
IMGUI_DIR = imgui/
OBJ_DIR = obj/
SRC_DIR = src/
NAME = RT-Online
SRC = 	main.cpp \
		GUI.cpp \
		Input.cpp \
		client.cpp


SOURCES = $(addprefix $(SRC_DIR), $(SRC))
SOURCES +=	$(IMPL_DIR)imgui_impl_glfw.cpp \
			$(IMPL_DIR)imgui_impl_opengl3.cpp
SOURCES += 	$(IMGUI_DIR)imgui.cpp \
			$(IMGUI_DIR)imgui_demo.cpp \
			$(IMGUI_DIR)imgui_draw.cpp \
			$(IMGUI_DIR)imgui_widgets.cpp 
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(basename $(notdir $(SOURCES)))))
UNAME_S := $(shell uname -s)

CXXFLAGS = -I$(IMPL_DIR) -I$(IMGUI_DIR) -Iincludes/
CXXFLAGS += -g
LIBS = -lpthread -lm
##---------------------------------------------------------------------
## OPENGL LOADER
##---------------------------------------------------------------------

## Using OpenGL loader: gl3w [default]
SOURCES += imgui/examples/libs/gl3w/GL/gl3w.c
CXXFLAGS += -Iimgui/examples/libs/gl3w -DIMGUI_IMPL_OPENGL_LOADER_GL3W

## Using OpenGL loader: glew
# (This assumes a system-wide installation)
# CXXFLAGS += -lGLEW -DIMGUI_IMPL_OPENGL_LOADER_GLEW

## Using OpenGL loader: glad
# SOURCES += imgui/libs/glad/src/glad.c
# CXXFLAGS += -Iimgui/libs/glad/include -DIMGUI_IMPL_OPENGL_LOADER_GLAD

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LIBS += -lGL `pkg-config --static --libs glfw3`

	CXXFLAGS += `pkg-config --cflags glfw3`
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "Mac OS X"
	LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
	LIBS += -L/usr/local/lib -L/opt/local/lib
	#LIBS += -lglfw3
	LIBS += -lglfw

	CXXFLAGS += -I/usr/local/include -I/opt/local/include
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(findstring MINGW,$(UNAME_S)),MINGW)
	ECHO_MESSAGE = "MinGW"
	LIBS += -lglfw3 -lgdi32 -lopengl32 -limm32

	CXXFLAGS += `pkg-config --cflags glfw3`
	CFLAGS = $(CXXFLAGS)
endif

##---------------------------------------------------------------------
## OUTPUT COLORS
##---------------------------------------------------------------------

C_RED = \033[31m
C_GREEN = \033[32m
C_MAGENTA = \033[35m
C_NONE = \033[0m

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

all: $(OBJ_DIR) $(NAME)
	@echo Build complete for $(ECHO_MESSAGE)

$(NAME): $(OBJS)
	@$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR):
	@mkdir obj

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR)%.o: $(IMPL_DIR)%.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR)%.o: $(IMGUI_DIR)%.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@


$(OBJ_DIR)%.o: $(IMGUI_DIR)examples/libs/gl3w/GL/%.c
	@$(CC) $(CXXFLAGS) -c $< -o $@
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

clean:
	@rm -rf $(OBJ_DIR)*
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_RED)[done]$(C_NONE)\n" $@

fclean: clean
	@rm -rf $(NAME)
	@printf "$(C_MAGENTA)$(NAME):$(C_NONE) %-25s$(C_RED)[done]$(C_NONE)\n" $@

re: fclean all