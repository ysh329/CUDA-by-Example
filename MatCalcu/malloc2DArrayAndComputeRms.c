#include "stdio.h"
#include "malloc.h"

int main(int argc,char* argv[])
{
	int elementNumInR = 8192;
	float (*a)[2] = malloc(sizeof(float)*elementNumInR*elementNumInR);
	a[0][0] = 1;
	a[0][1] = 2;
	a[1][0] = 3;
	a[1][1] = 4;
	a[2][0] = 5;
	a[2][1] = 6;

	for (int i = 0; i < elementNumInR; i++)
	{
		for (int j = 0; j < elementNumInR; j++)
		{

			fprintf(stdout, "%.2f\t", a[i][j]);
		}
		fprintf(stdout, "\n");
	}
}
