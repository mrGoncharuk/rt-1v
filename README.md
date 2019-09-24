# RT

### What is RT?

RT is a fully featured Raytracer built as a project at 42. This project is intended to be a four person six week project, however I decided to attempt it by myself. Ray tracing is a technique for rendering images by simulating the path of light through an image plane. This project uses .ini files to configure the input.

### Coding Style

At 42, we follow a strict norm in order to teach us to follow style guides. This norm also prevents us from using many built-in functions. In this project, we are limited to using a barebones graphic library called minilibx. This library limits the functionality to creating windows, handling input hooks, and coloring specific pixels.

### Usage

## Compile
For Mac(master) and Linux(linux_vers) there are several branches.
# Mac
- clone repository: git clone https://github.com/mrGoncharuk/rt-1v.git
- inside repository dir: make
- to execute binary file: ./RTv1 scenes/scene3.json 

# Linux
WARNING: you must have installed: clang compiler, SDL2, SDL2_image libraries
- clone repository: git clone https://github.com/mrGoncharuk/rt-1v.git
- change branch: git checkout linux_vers
- inside repository dir: make
- to execute binary file: ./RTv1 scenes/scene3.json

### Features
 
 - Scene parses from .json file
 - Reflections
 - Specularity effect
 - Camera rotation on arrows
 
### Images

