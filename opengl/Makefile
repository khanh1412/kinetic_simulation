CC		= g++
CXX_FLAGS	= -std=c++17 -g
INCLUDE		= -I./include -I./include/vendor -I/usr/include/cuda
LIB_FLAGS	= -lGL -lGLEW -lglfw -lcudart

NVCC		= nvcc
CUDA_CC		= cuda-g++ #gcc 7.x
CUDA_FLAGS	= -ccbin $(CUDA_CC) --default-stream per-thread


libnocuda: clean
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/Renderer.o sources/Renderer.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/VertexArray.o sources/VertexArray.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/VertexBuffer.o sources/VertexBuffer.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/VertexBufferLayout.o sources/VertexBufferLayout.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/IndexBuffer.o sources/IndexBuffer.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/Shader.o sources/Shader.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/Texture.o sources/Texture.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/stb_image.o sources/vendor/stb_image.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/Engine.o sources/Engine.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/Object.o sources/Object.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/Rectangle.o sources/Rectangle.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -shared -o libEngine.so objects/*.o

lib: clean
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/Renderer.o sources/Renderer.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/VertexArray.o sources/VertexArray.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/VertexBuffer.o sources/VertexBuffer.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/VertexBufferLayout.o sources/VertexBufferLayout.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/IndexBuffer.o sources/IndexBuffer.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/Shader.o sources/Shader.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/Texture.o sources/Texture.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/stb_image.o sources/vendor/stb_image.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/CudaResource.o sources/CudaResource.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/CudaBuffer.o sources/CudaBuffer.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/Engine.o sources/Engine.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/Object.o sources/Object.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o objects/Rectangle.o sources/Rectangle.cc
	$(CC) $(INCLUDE) $(CXX_FLAGS) -shared -o libEngine.so objects/*.o

main: lib
	$(CC) $(INCLUDE) $(CXX_FLAGS) -o run main.cc ./libEngine.so $(LIB_FLAGS)
normbuffer: lib
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o examples/7_normbuffer/main.o examples/7_normbuffer/main.cc
	$(NVCC) $(INCLUDE) $(CUDA_FLAGS) -dc -o examples/7_normbuffer/device.o examples/7_normbuffer/device.cu
	$(NVCC) $(INCLUDE) $(CUDA_FLAGS) -o run examples/7_normbuffer/*.o ./libEngine.so $(LIB_FLAGS) -lcudart
	rm -f examples/7_normbuffer/*.o
cuda: lib
	$(CC) $(INCLUDE) $(CXX_FLAGS) -c -fPIC -o examples/6_cuda/main.o examples/6_cuda/main.cc
	$(NVCC) $(INCLUDE) $(CUDA_FLAGS) -dc -o examples/6_cuda/device.o examples/6_cuda/device.cu
	$(NVCC) $(INCLUDE) $(CUDA_FLAGS) -o run examples/6_cuda/*.o ./libEngine.so $(LIB_FLAGS)
	rm -f examples/6_cuda/*.o
dynamic: lib
	$(NVCC) $(INCLUDE) $(CUDA_FLAGS) -o run examples/5_dynamic.cc ./libEngine.so $(LIB_FLAGS)

world: lib
	$(NVCC) $(INCLUDE) $(CUDA_FLAGS) -o run examples/4_world.cc ./libEngine.so $(LIB_FLAGS)

3d: lib
	$(NVCC) $(INCLUDE) $(CUDA_FLAGS) -o run examples/3_3d.cc ./libEngine.so $(LIB_FLAGS)

clean:
	rm -rf objects
	rm -f run
	rm -f *.so
	mkdir objects
