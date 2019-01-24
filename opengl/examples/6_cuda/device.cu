#include<cstdio>
__global__ void set_dynamic_position(float *arr, float t)
{
	int threadID = threadIdx.x;
	int blockID = blockIdx.x;
	int threads_per_block = blockDim.x;
	int i = blockID * threads_per_block + threadID;

	if (threadID == 0 or threadID == 1 or threadID == 2)
	{
		arr[i] = arr[i] * t;
	}
}

void device_set_dynamic_position(cudaStream_t stream, float *d_arr, float t)
{
	dim3 blocks_per_grid(4, 1, 1);
	dim3 threads_per_block(5, 1, 1);

	set_dynamic_position<<<blocks_per_grid, threads_per_block, 0, stream>>>(d_arr, t);
}
