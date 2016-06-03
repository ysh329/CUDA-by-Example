#include "malloc.h"
#include "stdio.h"

// CPU端初始化矩阵
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

// CPU端打印矩阵对应的向量
void vectorPrint(float *Vh, int elemNum)
{
	int i;

	for (i = 0; i < elemNum; i++)
	{
		printf("%2.2f ", *(Vh+i));
	}
	printf("\n");
}

// CPU端矩阵转置
void matrixTranspose(float *Ah, float *Bh, int rowElemNumInAh, int colElemNumInAh)
{
	int i, j;

	for (i = 0; i < rowElemNumInAh; i++)
	{
		for (j = 0; j < colElemNumInAh; j++)
		{
			*(Bh+rowElemNumInAh*j+i) = *(Ah+colElemNumInAh*i+j);
		}
	}
}

int main()
{
	// 变量初始化
	float *Ad, *Bd; // GPU设备端变量: Ad为原始矩阵, Bd为转置后矩阵
	float *Ah, *Bh; // CPU主机端变量: Bh为转置后矩阵

	// 设定原始矩阵A的维度
	int rowElemNumInA = 3, colElemNumInA = 5; // dimNum = 2
	int rowElemNumInB = colElemNumInA, colElemNumInB = rowElemNumInA;
	int size = sizeof(float) * rowElemNumInA * colElemNumInA;

	// CPU主机端申请空间
	Ah = (float*)malloc(size);
	Bh = (float*)malloc(size);

	// CPU端初始化原始矩阵A
	matrixInitialize(Ah, rowElemNumInA, colElemNumInA);

	// CPU端打印原始矩阵A
	matrixPrint(Ah, rowElemNumInA, colElemNumInA);

	// CPU端转置矩阵A后保存到矩阵B
	matrixTranspose(Ah, Bh, rowElemNumInA, colElemNumInA);

	// CPU端打印矩阵B
	printf("\n");
	matrixPrint(Bh, rowElemNumInB, colElemNumInB);

	// CPU端打印向量A和B
	printf("vector A:\n");
	vectorPrint(Ah, rowElemNumInA*colElemNumInA);
	printf("vector B:\n");
	vectorPrint(Bh, rowElemNumInB*colElemNumInB);

	// 释放CPU空间
	free(Ah);
	free(Bh);
	
	return 0;
}
