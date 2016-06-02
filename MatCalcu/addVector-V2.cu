#include "cuda.h"   // Unix系统下调用CUDA使用"cuda.h"，Win系统下调用CUDA使用"cuda.runtime"
#include "stdio.h"  // 标准输入输出，后面调用函数printf
#define  N	10000

__global__ void vectorAdd(float *A, float *B, float *C)
{
	int j = blockIdx.x * blockDim.x + threadIdx.x;
	int i = blockIdx.y * blockDim.y + threadIdx.y;

	C[i*N+j] = A[i*N+j] + B[i*N+j];
	printf("======================================================\n");
	printf("blockIdx.x:%d\tblockIdx.y:%d\n", blockIdx.x, blockIdx.y);
	printf("blockDim.x:%d\tblockDim.y:%d\n", blockDim.x, blockDim.y);
	printf("threadIdx.x:%d\tthreadIdx.y:%d\n", threadIdx.x, threadIdx.y);
	printf("i:%d j:%d C[i*N+j]:C[%2d]:%f\n", i, j, i*N+j, C[i*N+j]);
}

int main()
{
	// 设置使用的GPU下标(从0开始)
	// 多个GPU在终端用命令'nvidia-smi'查看下标
	int gpuDeviceIdx = 0;
	cudaSetDevice(gpuDeviceIdx);

	// 初始化设备(CPU)端变量
	// 使用cudaMalloc方法分配指定大小的空间
	float *Ad, *Bd, *Cd;
	int size = N*N*sizeof(float);
	cudaMalloc((void**)&Ad, size);
	cudaMalloc((void**)&Bd, size);
	cudaMalloc((void**)&Cd, size);

	// 设置程序在GPU上运行参数
	//	1.grid下的block数目
	//	2.block下的thread数目
	dim3 bpg(10, 10); // 每个网格下的线程块个数(block num. per grid)
					// bpg(blockDim.x, blockDim.y)
	dim3 tpb(10, 10); // 每个线程块下的线程个数(thread num. per block)
					// tpb(threadIdx.x, threadIdx.y)

	// 根据资源分配的参数
	// 在GPU上执行核函数(__global__修饰的函数)
	vectorAdd<<<bpg, tpb>>>(Ad, Bd, Cd);

	// 释放空间
	cudaFree(Ad);
	cudaFree(Bd);
	cudaFree(Cd);

	return 0;
}
