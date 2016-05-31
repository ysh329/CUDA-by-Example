#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "math.h"
#include <time.h>

int main(void)
{
	int elementNumInR = 10;
	int arrayDim = 2;

	int i = 0, j = 0;
	float *R = NULL, Rms = 0.0, ma = 0.0, mi = RAND_MAX;
	R = (float*)malloc(sizeof(float)*elementNumInR);
	float (*A)[arrayDim] = malloc(sizeof(float)*elementNumInR*elementNumInR);

	srand((unsigned) time(NULL));

	for (i = 0; i < elementNumInR; i++)
	{
		R[i] = rand()/(RAND_MAX+10e-5);
		Rms += R[i]*R[i];

	}
	Rms = sqrt(Rms);

	for (i = 0; i < elementNumInR; i++)
	{
		for (j = 0; j < elementNumInR; j++)
		{
			A[i][j] = R[i] * R[j] / Rms;
			if (A[i][j] - ma > 1e-10)
			{
				ma = A[i][j];
			}
			if (A[i][j] - mi < 1e-10)
			{
				mi = A[i][j];
			}
		}
	}
	fprintf(stdout, "ma = %f\n", ma);
	fprintf(stdout, "mi = %f\n", mi);

	// Print R
	/*
	for (int i = 0; i < elementNumInR; i++)
	{
		for (int j = 0; j < elementNumInR; j++)
		{

			fprintf(stdout, "%f\t", A[i][j]);
		}
		fprintf(stdout, "\n");
	}*/

	//fprintf(stdout, "sizeof(R)/sizeof(R[0]):%ld\n", sizeof(R)/sizeof(R[0]));
	//fprintf(stdout, "sizeof(A)/sizeof(A[0]):%ld\n", sizeof(A)/sizeof(A[0][0]));
	//fprintf(stdout, "sizeof(A)/sizeof(A[0])/sizeof(A[0][0]):%ld\n", sizeof(A)/sizeof(A[0])/sizeof(A[0][0]));

	free(A);
	free(R);
	return 0;
}
