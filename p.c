#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <omp.h>
#define SIZE 10000
double a[SIZE][SIZE];
int i;
double  b[SIZE][SIZE];
double  c[SIZE][SIZE];

void main( int argc, char **argv )
{
// initialising matrixes
	int i = 0, j = 0;
	for ( i = 0; i < SIZE; i++)
		for ( j = 0; j < SIZE; j ++){
			b[i][j] = 1;
			c[i][j] = 2;
			a[i][j] = 0;
		}
	clock_t begin;
	clock_t end;
  int k;
//no optimisation 
  begin = clock();
  
	  for( j = 0; j < SIZE; j++ ) {
		for( i = 0; i < SIZE; i++ ) {
		  a[i][j] = b[i][j]+c[i][j];
		}
	  }
		
	  
  end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Execution time is :%f seconds \n", time_spent);

// optimisation step 1
	begin = clock();
	for (i = 0; i < SIZE; i ++){
		for (j = 0; j < SIZE; j ++){
			a[i][j] = b[i][j] + c[i][j];
		}
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Execution time after optimisation-1 is :%f seconds \n", time_spent);
//optimisation step 2
int step = 9;
begin = clock();
	#pragma parallel for
	for (i = 0; i < SIZE; i ++){
		for (j = 0; j < SIZE - step; j += step){
			a[i][j] = b[i][j] + c[i][j];
			a[i][j+1] = b[i][j+1] + c[i][j+1];
			a[i][j+2] = b[i][j+2] + c[i][j+2];
			a[i][j+3] = b[i][j+3] + c[i][j+3];
			a[i][j+4] = b[i][j+4] + c[i][j+4];
			a[i][j+5] = b[i][j+5] + c[i][j+5];
			a[i][j+6] = b[i][j+6] + c[i][j+6];
			a[i][j+7] = b[i][j+7] + c[i][j+7];
			a[i][j+8] = b[i][j+8] + c[i][j+8];
		}
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Execution time after optimisation 2 is :%f seconds \n", time_spent);

// optimisation with pragma parallel
 step = 9;
 double wall_timer = omp_get_wtime();
	#pragma parallel for
	for (i = 0; i < SIZE; i ++){
		#pragma parallel for
		for (j = 0; j < SIZE - step; j += step){
			a[i][j] = b[i][j] + c[i][j];
			a[i][j+1] = b[i][j+1] + c[i][j+1];
			a[i][j+2] = b[i][j+2] + c[i][j+2];
			a[i][j+3] = b[i][j+3] + c[i][j+3];
			a[i][j+4] = b[i][j+4] + c[i][j+4];
			a[i][j+5] = b[i][j+5] + c[i][j+5];
			a[i][j+6] = b[i][j+6] + c[i][j+6];
			a[i][j+7] = b[i][j+7] + c[i][j+7];
			a[i][j+8] = b[i][j+8] + c[i][j+8];
		}
	}
	//end = clock();
	//time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Execution time after optimisation 3 is :%f seconds \n",  omp_get_wtime() - wall_timer);
}
