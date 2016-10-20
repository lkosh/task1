#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#define SIZE 10000
double a[SIZE][SIZE];
int i;
double  b[SIZE][SIZE];
double  c[SIZE][SIZE];
int thread1_exited, thread2_exited;
void *thread1_start(void *arg){
	int errflag;
	errflag = pthread_detach(pthread_self());
	if (errflag){
		pthread_exit(NULL);
		return;
	}
	printf("thread1\n");
	int i, j = 0;
	for (i = 0 ; i < SIZE/2; i ++)
		for (j = 0 ; j < SIZE; j ++)
			a[i][j] = b[i][j] + c[i][j];
	thread1_exited = 1;
}

void *thread2_start(void *arg){
	int errflag;
	errflag = pthread_detach(pthread_self());
	if (errflag){
		pthread_exit(NULL);
		return;
	}
		printf("thread2\n");
	int i, j = 0;
	for (i = SIZE/2 ; i < SIZE; i ++)
		for (j = 0 ; j < SIZE; j ++)
			a[i][j] = b[i][j] + c[i][j];
	thread2_exited = 1;
}
void main( int argc, char **argv )
{
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
  begin = clock();
  
	  for( j = 0; j < SIZE; j++ ) {
		for( i = 0; i < SIZE; i++ ) {
		  a[i][j] = b[i][j]+c[i][j];
		}
	  }
		
	  
  end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Execution time is :%f seconds \n", time_spent);


	begin = clock();
	for (i = 0; i < SIZE; i ++){
		for (j = 0; j < SIZE; j ++){
			a[i][j] = b[i][j] + c[i][j];
		}
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Execution time after optimisation is :%f seconds \n", time_spent);
	
	
	
	
	for ( i = 0; i < SIZE; i++)
		for ( j = 0; j < SIZE; j ++){
			b[i][j] = 1;
			c[i][j] = 2;
			a[i][j] = 0;
		}
	begin = clock();
	int errflag;
	pthread_t thread1, thread2;
	errflag = pthread_create(&thread1, NULL, thread1_start, NULL);
	if (errflag){
		printf("Error creating a thread\n");
		exit(1);
	}
	
	errflag = pthread_create(&thread2, NULL, thread2_start, NULL);
	if (errflag){
		printf("Error creating a thread\n");
		exit(1);
	}
	int fl = 1;
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Execution time after optimisation with threads is :%f seconds \n", time_spent);
	while (!thread1_exited || !thread2_exited){}
	/*for (i = 0; i < SIZE; i ++){
		for (j = 0; j < SIZE; j ++){
		
				printf (" %01.0f",  a[i][j]);
			}
		printf("\n");
			}
		
	if (fl)
		printf("ok ! \n");
	else printf ("%f", a[0][0]);
		
	
	*/
	
}
