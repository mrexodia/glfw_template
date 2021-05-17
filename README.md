# imgui_template

Simple template to get started with [Dear ImGui](https://github.com/ocornut/imgui) using [GLFW](https://www.glfw.org/docs/latest/quick_guide.html) and [GLEW](https://github.com/nigels-com/glew).

This template uses [cmkr](https://github.com/MoAlyousef/cmkr) together with [vcpkg](https://github.com/microsoft/vcpkg) for frictionless cross platform dependency management with CMake.

## Building (IDE)

Clone this repository and open it in your favorite IDE with CMake support ([Visual Studio](https://visualstudio.microsoft.com/), [CLion](https://www.jetbrains.com/clion/), [Qt Creator](https://www.qt.io/product/development-tools)). Everything should work out of the box.

## Building (command line)

```sh
cmake -B build
cmake --build build
```

**Note:** On Ubuntu you need to run `sudo apt-get install libgl-dev libxinerama-dev libxcursor-dev xorg-dev libglu1-mesa-dev` to use this template.

## cmake.toml

Under the hood cmkr generates the `CMakeLists.txt` required to build this project from the `cmake.toml` file:

```toml
[cmake]
version = "3.15"
cmkr-include = "cmake/cmkr.cmake"

[project]
name = "imgui_template"

# See https://github.com/microsoft/vcpkg#getting-started on how to use vcpkg
# Chose a version from https://github.com/microsoft/vcpkg/releases
# During CMake configuration you will be told how to find and link to the packages
[vcpkg]
version = "2021.05.12"
packages = ["glfw3", "GLEW"]

# vcpkg will download the packages, but you still need to find them to use them
[find-package]
glfw3 = {}
GLEW = {}

[target.imgui]
type = "static"
sources = [
    "third_party/imgui/*.cpp",
    "third_party/imgui/*.h",
    "third_party/imgui/backends/imgui_impl_glfw.cpp",
    "third_party/imgui/backends/imgui_impl_glfw.h",
    "third_party/imgui/backends/imgui_impl_opengl3.cpp",
    "third_party/imgui/backends/imgui_impl_opengl3.h",
]
include-directories = ["third_party/imgui"]
link-libraries = ["glfw", "GLEW::GLEW"]
compile-features = ["cxx_std_11"]

[target.example]
type = "executable"
sources = ["src/main.cpp"]
link-libraries = ["imgui"]

```
