#ifndef _CUDA_BUFFER_
#define _CUDA_BUFFER_
#include<cstddef>
class CudaBuffer
{
	private:
		void *h_ptr;
		size_t size;
		bool writable;

	public:
		CudaBuffer(void *data, size_t size);
		CudaBuffer(size_t size);
		~CudaBuffer();

		void setData(void *data, size_t size);
		void Bind() const {};
		void Unbind() const {};

		inline size_t getSize() const {return size;}
		inline void *getHostPointer() const {return h_ptr;}	
};
#endif
