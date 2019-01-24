#include"CudaBuffer.h"
#include<iostream>
CudaBuffer::CudaBuffer(void *data, size_t size)
	: h_ptr(data), size(size), writable(false)
{}
CudaBuffer::CudaBuffer(size_t size)
	: h_ptr(nullptr), size(size), writable(true)
{}
CudaBuffer::~CudaBuffer()
{}

void CudaBuffer::setData(void *data, size_t size)
{
	if (not writable) return;
	if (size > this->size)
	{
		std::cout<<"Set a larger data than buffer size!"<<std::endl;
		__builtin_trap();
	}
	else 
	{
		if (size < this->size)
			std::cout<<"Set a smaller data than buffer size!"<<std::endl;
		h_ptr = data;
	}
}
