#include "malloc.h"
#include "stdio.h"

void vectorInitialize(float *Ah, int elemNum)
{
    float summ = 0.0;
    int i;

    for (i = 0; i < elemNum; i++)
    {   
		summ += 1.0;
		//*(Ah+sizeof(float)*i) = summ;
		*(Ah+i) = summ;
	}
}

void vectorPrint(float *Ah, int elemNum)
{
    int i;

    for (i = 0; i < elemNum; i++)
    {
		//printf("%f\t", *(Ah+sizeof(float)*i));
		printf("%f\t", *(Ah+i));
	}
	printf("\n");
}

int main()
{
    // 变量初始化
    float *Ad, *Bd; // GPU设备端变量
	float *Ah, *Bh; // CPU主机端变量

    // 设定原始矩阵A的维度
    int elemNum = 5; // dimNum = 2
    int size = sizeof(float) * elemNum;

	// CPU主机端申请空间
	Ah = (float*)malloc(size);
	//Bh = (float*)malloc(size);

	// GPU设备端申请空间    
	//cudaMalloc((void**)&Ad, size);
	//cudaMalloc((void**)&Bd, size);
 
	// 初始化原始向量A
	vectorInitialize(Ah, elemNum);

    // 打印原始矩阵A
    vectorPrint(Ah, elemNum);

	return 0;
}
