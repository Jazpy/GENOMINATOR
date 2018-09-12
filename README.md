# GENOMINATOR

Genome visualizer in C++ with OpenGL. This will only render pretty things based on a genome, and is not intended for any serious use.

## Prerequisites

In order to compile this project, the following must be installed:

- GLEW
- GLFW
- GLM
- OpenGL 4.0+

Please check [this site](http://www.opengl-tutorial.org/) for instructions. You can also check the tutorials this is based off of at @opengl-tutorials

## Building

Use the `CMakeLists.txt` file to generate a makefile inside the `build/` directory. I recommend using `cmake-gui` for this. Then simply use the `make` command. An executable named `genominator` should be generated.
