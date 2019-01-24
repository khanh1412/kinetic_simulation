#include<cstdio>
__global__ void set_dynamic_positions(float *arr, float t)
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
__global__ void set_dynamic_indices(unsigned int *d_all_ib, unsigned int *d_ib, int flip)
{
	if (flip == blockIdx.x)
	{
		d_ib[threadIdx.x] = d_all_ib[blockDim.x * blockIdx.x + threadIdx.x];
		d_ib[3 + threadIdx.x] = 0;
	}
}

void device_set_dynamic_positions(cudaStream_t stream, float *d_arr, float t)
{
	dim3 blocks_per_grid(4, 1, 1);
	dim3 threads_per_block(5, 1, 1);

	set_dynamic_positions<<<blocks_per_grid, threads_per_block, 0, stream>>>(d_arr, t);
}
static int flip = 1;
void device_set_dynamic_indices(cudaStream_t stream, unsigned int *d_all_ib, unsigned int *d_ib)
{
	flip = (flip + 1) % 2;
	dim3 blocks_per_grid(2, 1, 1);
	dim3 threads_per_block(3, 1, 1);

	set_dynamic_indices<<<blocks_per_grid, threads_per_block, 0, stream>>>(d_all_ib, d_ib, flip);


	unsigned int arr[6];
	cudaStreamSynchronize(stream);
	cudaMemcpyAsync(&(arr[0]), d_ib, 6*sizeof(unsigned int), cudaMemcpyDeviceToHost, stream);
	cudaStreamSynchronize(stream);
	std::printf("\nflip = %d\n", flip);
	std::printf("%d %d %d\n", arr[0], arr[1], arr[2]);
	std::printf("%d %d %d\n", arr[3], arr[4], arr[5]);
}
