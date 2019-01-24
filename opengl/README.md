# opengl and cuda

cross platform opengl with cuda supports.

This repository holds the code of OpenGL API abstraction with CUDA integration written in C++

https://youtu.be/G___d39DK1g

https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART__OPENGL.html#group__CUDART__OPENGL

# Requirements

- `GLEW`

- `GLFW`

- `CUDA`

# Included Vendor code

- `GLM` : https://github.com/g-truc/glm

- `stb_image` : https://github.com/nothings/stb

# Features


- `OpenGL`		: VertexArray, VertexBuffer, IndexBuffer, Shader, Texture.

- `CUDA GLBuffer`	: GLBuffer can be read and written by Cuda.

- `CUDA Buffer`		: Create CUDA buffer to do computation later.

- `Draw Engine`		: An engine that takes in objects then draw them.


# Tested

- Nvidia GPU + Windows 10 : still works, but I have stopped Windows supports.

- Nvidia GPU + Fedora 29 : works

- AMD GPU + Fedora 29 : works without CUDA

- Intel GPU + Fedora 29 : does not work, GLSL version problem!
