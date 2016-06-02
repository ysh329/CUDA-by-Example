#include	  "cuda.h"
#define		  N			  1000

__device__	  float		  A[N][N];
__device__	  float		  B[N][N];
__device__    float       C[N][N];

__global__ void vectorAdd(float A[N][N], float B[N][N], float C[N][N])
{
	int i = threadIdx.x;
	int j = threadIdx.y;
	C[i][j] = A[i][j] + B[i][j];
}

int main()
{
	int bpg = 1;
	dim3 tpb(N, N);
	vectorAdd<<<bpg, tpb>>>(A, B, C);

	cudaFree(A);
	cudaFree(B);
	cudaFree(C);
	return 0;
}
