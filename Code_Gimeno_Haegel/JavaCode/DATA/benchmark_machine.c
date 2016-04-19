#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MIN(i, j) (i < j ? i : j)

const int HEURISTIC_ITERATIONS = 7346;

const int M = 2048;
const int N = 16384;

static unsigned int nSeed = 5323;
static unsigned int rndMax = 32767;

/* 
 * We are implementing a simple random generator since the values generated by rand() in c/c++
 * varies from compiler to compiler and we want it to be consistent across platforms
 */
unsigned int rnd()
{
	nSeed = (8253729 * nSeed + 2396403);
	return(nSeed % rndMax);
}

/* 
 * This method just iterates a predefined number of times where each iteration
 * simulates a neighbourhood making a simple swap in the current solution
 */
void heuristic(int ** A, int * x)
{
    int it, i, j, j2;
	
	for (it = 0; it < HEURISTIC_ITERATIONS; it++)
	{
		j = rnd() % N;
		if (x[j] == 0)
		{
			x[j] = 1;
			for (i = 0; i < M; i++)
			{
				if (A[i][j] == 1)
				{
					for (j2 = 0; j2 < N; j2++)
					{
						if (A[i][j2] == 1) x[j2] = 0;
					}
				}
			}
		}
		else x[j] = 0;
	}
}

// This method generates the model that will be used for the benchmarking
void generatemodel(int ** A)
{
    int i, j;
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (rnd() <  2 * rndMax / 3) A[i][j] = 0;
			else A[i][j] = 1;
		}
	}
}

void resetsolution(int * x)
{
    int j;
	for (j = 0; j < N; j++)
	{
		x[j] = 0;
	}
}

int main()
{
	printf("\n%s\n%s\n\n%s\n%s\n%s\n\n%s\n%s\n\n%s\n", 
		"Benchmarking Program for the DTU Metaheuristics Competition 2015",
		"================================================================",
		"This is a tool provided to benchmark your machine to see how",
		"much time you should use when parameter tuning your algorithm",
		"for the competition.",
		"Make sure that no unnecessary windows are open or other CPU",
		"consuming programs are running",
		"Press ENTER to start the benchmarking");
	
	getchar();
	
	int i, j;
	
	int ** A;
	int * x;
	int * memblock;
	
	memblock = malloc(M * N * sizeof(int));
	A = malloc(M * sizeof(int *));
	for (i = 0; i < M; i++)
	{
		A[i] = &memblock[i * N];
	}
	x = malloc(N * sizeof(int));
	
	generatemodel(A);
	
	time_t start, stop;
	
	printf("Benchmarking computer. Please wait...\n");

	time(&start);
	resetsolution(x);
	heuristic(A, x);
	time(&stop);
	
	printf("Your algorithm should be tuned on this computer with a\ntime limit of %.2f seconds.\n\nPress ENTER to exit.\n", difftime(stop, start));
	getchar();
	
	free(A[0]);
	free(A);
	free(x);

	return 0;
}