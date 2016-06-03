#include "cuda.h"
#include "malloc.h"
#include "stdio.h"

#define N 4

// GPU端矩阵转置
__global__ void matrixTranspose(float *Ad, float *Bh, int rowElemNumInAd, int colElemNumInAd)
{
	int cCol = threadIdx.x; 
	int cRow = threadIdx.y;
	*(Bh+rowElemNumInAd*cCol+cRow) = *(Ad+colElemNumInAd*cRow+cCol);
}

// CPU端矩阵初始化
void matrixInitialize(float *Ah, int rowElemNum, int colElemNum)
{
	float summ = 0.0;
	int i, j;

    for (i = 0; i < rowElemNum; i++)
    {
        for (j = 0; j < colElemNum; j++)
        {   
			summ += 1.0;
			*(Ah+colElemNum*i+j) = summ; 
		}
    }
}

// CPU端打印矩阵
void matrixPrint(float *Ah, int rowElemNum, int colElemNum)
{
	int i, j;

	for (i = 0; i < rowElemNum; i++)
	{
		for (j = 0; j < colElemNum; j++)
		{
			printf("%2.2f \t", *(Ah+colElemNum*i+j));
		}
		printf("\n");
	}
}

// CPU端打印矩阵展平后对应的向量
__host__ void vectorPrint(float *Vh, int elemNum)
{
	int i;

	for (i = 0; i < elemNum; i++)
	{
		printf("%2.2f ", *(Vh+i));
	}
	printf("\n");
}

int main()
{
	// 变量初始化
	float *Ad, *Bd; // GPU设备端变量: Ad为原始矩阵, Bd为转置后矩阵
	float *Ah, *Bh; // CPU主机端变量: Bh为转置后矩阵

	// 设定原始矩阵A的维度
	int rowElemNumInA = N, colElemNumInA = N*rowElemNumInA; // dimNum = 2
	int rowElemNumInB = colElemNumInA, colElemNumInB = rowElemNumInA;
	int size = sizeof(float) * rowElemNumInA * colElemNumInA;

	// GPU参数初始化
    // 设置使用的GPU下标(从0开始)
    // 多个GPU在终端用命令'nvidia-smi'查看下标
    int gpuDeviceIdx = 0;
    cudaSetDevice(gpuDeviceIdx);

	// CPU主机端申请空间
	Ah = (float*)malloc(size);
	Bh = (float*)malloc(size);

	// GPU设备端申请空间	
	cudaMalloc((void**)&Ad, size);
	cudaMalloc((void**)&Bd, size);

	// CPU端初始化原始矩阵A
	matrixInitialize(Ah, rowElemNumInA, colElemNumInA);

	// CPU端打印原始矩阵A
	matrixPrint(Ah, rowElemNumInA, colElemNumInA);

	// GPU端转置矩阵Ad后保存到矩阵Bh
    // 设置程序在GPU上运行参数
    //  1.grid下的block数目
    //  2.block下的thread数目
    dim3 bpg(1, 1); // 每个网格下的线程块个数(block num. per grid)
                      // bpg(blockDim.x, blockDim.y)
    dim3 tpb(N, N*N); // 每个线程块下的线程个数(thread num. per block)
                    // tpb(threadIdx.x, threadIdx.y)
    // 根据资源分配的参数
    // 在GPU上执行核函数(__global__修饰的函数)
    matrixTranspose<<<bpg, tpb>>>(Ah, Bd, rowElemNumInA, colElemNumInA);


	// 从GPU端拷贝矩阵Bd到CPU端Bh
	cudaMemcpy(Bh, Bd, size, cudaMemcpyDeviceToHost);

	// 打印矩阵Bh
	printf("\n");
	matrixPrint(Bh, rowElemNumInB, colElemNumInB);


	// 打印向量A和B
	printf("vector A:\n");
	vectorPrint(Ah, rowElemNumInA*colElemNumInA);
	printf("vector B:\n");
	vectorPrint(Bh, rowElemNumInB*colElemNumInB);


	// 释放CPU和GPU空间
	free(Ah);
	free(Bh);
	cudaFree(Ad);
	cudaFree(Bd);

	return 0;
}
