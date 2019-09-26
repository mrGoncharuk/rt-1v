# RT

### What is RT?

RT is a fully featured Raytracer built as a project at 42. This project is intended to be a four person six week project, however I decided to attempt it by myself. Ray tracing is a technique for rendering images by simulating the path of light through an image plane. This project uses .ini files to configure the input.

### Coding Style

At 42, we follow a strict norm in order to teach us to follow style guides. This norm also prevents us from using many built-in functions. In this project, we are limited to using a barebones graphic library called minilibx. This library limits the functionality to creating windows, handling input hooks, and coloring specific pixels.

# Usage

For Mac(master) and Linux(linux_vers) there are several branches.
## Mac
- clone repository: git clone https://github.com/mrGoncharuk/rt-1v.git
- inside repository dir: make
- to execute binary file: ./RTv1 scenes/scene3.json 

## Linux
WARNING: before to compile on linux you must have installed clang compiler, SDL2 and SDL2_image libraries
- clone repository: git clone https://github.com/mrGoncharuk/rt-1v.git
- change branch: git checkout linux_vers
- inside repository dir: make
- to execute binary file: ./RTv1 scenes/scene3.json

# Features
 
 - Scene parses from .json file
 - 4 basic shapes
 - 3 types of light sources
 - Reflections
 - Specularity effect
 - Camera rotation on arrows
 
# Screenshots
![rt_screen1](https://user-images.githubusercontent.com/28892426/65695254-d9bcac80-e07f-11e9-965c-8044bf717978.png)
![rt_screen2](https://user-images.githubusercontent.com/28892426/65695255-d9bcac80-e07f-11e9-9ba8-be9d59fa3b50.png)
![rt_screen3](https://user-images.githubusercontent.com/28892426/65695256-d9bcac80-e07f-11e9-9fb4-820eaff524e6.png)
![rt_screen4](https://user-images.githubusercontent.com/28892426/65695257-d9bcac80-e07f-11e9-9306-1a32781c2f84.png)
![rt_screen5](https://user-images.githubusercontent.com/28892426/65695258-da554300-e07f-11e9-89ad-be03cd36b078.png)
![rt_screen6](https://user-images.githubusercontent.com/28892426/65695259-da554300-e07f-11e9-9f2c-0cb0d6e930f6.png)

