# moonshine
An unstable, sometimes intoxicating, yet tasty sandbox for testing OpenGL 4.5.

Actually, it's quite intoxicating at the moment; there are better sandboxes out there!

## Requirements
* A C++17 compiler
* A video card with support for OpenGL 4.5 or later
* [CMake](http://www.cmake.org/) (version 3.8 or later)
* [glfw](http://www.glfw.org/) (version 3.2 or later)
* [fmt](http://fmtlib.net/) (version 3.0 or later)
* [spdlog](https://github.com/gabime/spdlog) (version 1.1.0 or later)
* [Dear ImGui](https://github.com/ocornut/imgui) (version 1.65 or later)
* [Catch2](https://github.com/catchorg/Catch2) (version 2.1 or later)

## Build instructions
### Linux
Use your favorite package manager to fetch your packages. For instance, on Fedora, do something like:
``` 
$ sudo dnf install cmake glfw fmt spdlog
```
Then you can simply run your favorite CMake frontend (cmake-gui, cmake-curses or simply cmake at the command line). There is no option to configure at the moment.

### Windows
Consider using [vcpkg](https://github.com/Microsoft/vcpkg) with Visual Studio 2017; it works surprisingly well.
```
> .\vcpkg.exe install glfw3 fmt spdlog imgui
```
