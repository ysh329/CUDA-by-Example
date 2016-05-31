#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "math.h"
#define  elementNum 3

int main(void)
{
	int i = 0, j = 0;
	float *R = NULL;
	R = (float*)malloc(sizeof(float)*elementNum);
	float Rms, Min, Max;
	float (*A)[elementNum] = malloc(sizeof(float)*elementNum*elementNum);

	// int (*a)[2] = malloc(sizeof(int)*3*2)
	// Set current time as seed
	srand((unsigned) time(NULL));

	// Check R == NULL
	if (R == NULL)
	{ /* malloc failed */
		fprintf(stderr, "MEMORY ERROR");
		return -1;
    }

    // Initialize R with random float point
    for (i = 0; i < elementNum; i++)
    {
        R[i] = rand()/100;
        Rms = Rms + R[i]*R[i];
        //fprintf(stdout, "R[%d]:%f\n", i, R[i]);
    }

	// Prinf R
	for (i = 0; i < elementNum; i++)
	{
		fprintf(stdout, "%.4f", R[i]);
	}
	fprintf(stdout, "\n");


    Rms = sqrt(Rms);
    Min = Max = R[0]*R[0]/Rms;
    for (i = 1; i < elementNum; i++)
    {
        for(j = 1; j < elementNum; j++)
        {
			A[i][j] = (R[i]*R[j])/Rms;
			if(A[i][j] - Min < -0.00001)
			{
				Min = A[i][j];
			}
			if(A[i][j] - Max > 0.00001)
			{
				Max = A[i][j];
			}
		}
	}
    fprintf(stdout, "Min:%f \nMax:%f\n", Min, Max);

    // Prinf A
    for (i = 0; i < elementNum; i++)
    {
		for (j = 0; j < elementNum; j++)
        {
			fprintf(stdout, "%.4f\t", A[i][j]);
		}
		fprintf(stdout, "\n");
	}

    // Free space
    free(R);
    free(A);
    return 0;
}
