# Picasso Game Engine
![Picasso Logo](https://github.com/karonte691/Picasso/assets/1017628/afc2f6b2-6446-4dfd-8bc1-734af720ff7b)

## Overview

Picasso is a cross-platform game engine written in C++ designed to support 2D and 3D games. Currently in its alpha stage, Picasso was created as a learning project to understand C++ and is not intended for professional use.

Inspired by the need to learn and improve C++ skills.
Thanks to the open-source community for providing resources and libraries.

![Demo](https://github.com/karonte691/Picasso/assets/1017628/3053fa6a-1380-4a6e-8727-b90415d9d8b8)

## Features

- **Texture Support**: Manages textures for rendering images in games.
- **Mesh Support**: Manages meshes for representing 3D models.
- **Support for Linux e Windows** the code is written to be agnostic regarding the operating system is running on
- **Graphics Drivers**:
  - Vulkan
  - OpenGL

## Upcoming Developments

- **Scene Management**: Organizing and managing game objects and their interactions.
- **Audio Support**: Implementing an audio system for sound effects and background music.
- **Additional Features**: Continual improvements and additions as development progresses.
- **Support for DirectX**

## Getting Started

### Prerequisites

- C++ Compiler (e.g., GCC, Clang, MSVC)
- CMake
- Vulkan SDK (for Vulkan support)
- OpenGL Libraries (for OpenGL support)

## Dependencies

Picasso relies on several external libraries. Ensure that the following libraries are installed on your system:

- **X11**: `libX11.so.6.4.0`
- **X11-xcb**: `libX11-xcb.so.1.0.0`
- **xcb**: `libxcb.so.1.1.0`
- **Vulkan**: `libvulkan.so`
- **SOIL**: `libSOIL.so`
- **OpenGL**: `libGL.so`
- **GLFW**: `libglfw.so`
- **GLEW**: `libGLEW.so`
- **GLU**: `libGLU.so`

### Modifying CMakeLists.txt

To compile Picasso, you need to modify the `CMakeLists.txt` file in the `PEngine` directory to correctly reference the paths to these libraries. Here is an example of how to link these libraries in your `CMakeLists.txt`:

```cmake
target_link_libraries(PEngine /usr/lib/x86_64-linux-gnu/libX11.so.6.4.0)
target_link_libraries(PEngine /usr/lib/x86_64-linux-gnu/libX11-xcb.so.1.0.0)
target_link_libraries(PEngine /usr/lib/x86_64-linux-gnu/libxcb.so.1.1.0)
target_link_libraries(PEngine /usr/lib/x86_64-linux-gnu/libvulkan.so)
target_link_libraries(PEngine /usr/lib/libSOIL.so)
target_link_libraries(PEngine /usr/lib/x86_64-linux-gnu/libGL.so)
target_link_libraries(PEngine /usr/lib/x86_64-linux-gnu/libglfw.so)
target_link_libraries(PEngine /usr/lib/x86_64-linux-gnu/libGLEW.so)
target_link_libraries(PEngine /usr/lib/x86_64-linux-gnu/libGLU.so)
```

In the future, the makefile will load these libraries without needing to specify the path

### Building Picasso

1. Clone the repository:
   ```sh
   git clone https://github.com/karonte691/Picasso.git
   cd Picasso
    ```

2.  Create a build directory:

    ```sh
    mkdir build
    cd build
    ```

3. Configure the project with CMake:

     ```sh
    cmake ..
    ```

4. Build the project:

   ```sh
    cmake ..
   ```
5. Run Picasso
   ```sh
   ./Build/PRunner
   ```

### Contributing

Contributions are welcome! Please fork the repository and create a pull request for any feature additions or bug fixes. Ensure your code follows the existing coding style and includes appropriate tests.
License

This project is licensed under the MIT License. See the LICENSE file for details.
Acknowledgments
