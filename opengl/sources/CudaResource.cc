#include"CudaResource.h"
CudaResource::CudaResource(VertexBuffer *vb)
	: stream(0), Buffer(vb), d_ptr(nullptr), size(0), type(OPENGL_BUFFER)
{
	Register(vb->getID());
}
CudaResource::CudaResource(IndexBuffer *ib)
	: stream(0), Buffer(ib), d_ptr(nullptr), size(0), type(OPENGL_BUFFER)
{
	Register(ib->getID());
}
CudaResource::CudaResource(Texture *t)
	: stream(0), Buffer(t), d_ptr(nullptr), size(0), type(IMAGE)
{
	Register(t->getID());
}
CudaResource::CudaResource(CudaBuffer *nb)
	: stream(0), Buffer(nb), d_ptr(nullptr), size(0), type(CUDA_BUFFER)
{}
CudaResource::~CudaResource()
{
	Unmap();
	Unregister();
}
inline void CudaResource::Register(unsigned int ID)
{
	if (type == OPENGL_BUFFER)
	{
		if (cudaSuccess != cudaGraphicsGLRegisterBuffer(&resource, ID, cudaGraphicsRegisterFlagsNone))
			__builtin_trap();
	}
	else if (type == IMAGE)
	{
		if (cudaSuccess != cudaGraphicsGLRegisterImage(&resource, ID, GL_TEXTURE_2D, cudaGraphicsRegisterFlagsNone))
			__builtin_trap();
	}

}
inline void CudaResource::Unregister()
{
	if (type == OPENGL_BUFFER)
		cudaGraphicsUnregisterResource(resource);
}

void CudaResource::Map()
{
	if (type != CUDA_BUFFER)
	{
		if (cudaSuccess != cudaGraphicsMapResources(1, &resource, stream))
			__builtin_trap();
		cudaGraphicsResourceSetMapFlags(resource, cudaGraphicsMapFlagsNone);
		cudaGraphicsResourceGetMappedPointer(&d_ptr, &size, resource);
	}
	else
	{
		size = reinterpret_cast<CudaBuffer*>(Buffer)->getSize();
		void *h_ptr = reinterpret_cast<CudaBuffer*>(Buffer)->getHostPointer();
		cudaMalloc(&d_ptr, size);
		cudaMemcpyAsync(d_ptr, h_ptr, size, cudaMemcpyHostToDevice, stream);
	}
}
void CudaResource::Unmap()
{
	if (type != CUDA_BUFFER)
	{
		if(d_ptr)
		{
			cudaGraphicsUnmapResources(1, &resource, stream);
			d_ptr = nullptr;
			size = 0;
		}
	}
	else
	{
		cudaFree(d_ptr);
		d_ptr = nullptr;
		size = 0;
	}
}



