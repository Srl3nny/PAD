#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 2

pthread_t callThd[NUM_THREADS];
pthread_mutex_t mutexpi;
static long num_steps = 1000000;
double sum = 0.0;
double step;


void *calpi(void *arg)
{
	int i;
	double x, sum_parcial = 0.0;
	int offset;
	offset = (int)arg;
	int len = (int) num_steps/(int)NUM_THREADS;
	int start = len * (int) offset;
	int fim = (start + len) -1;
	printf("thread %i com start %i e fim %i\n", offset,start,fim);

  for (i=start; i<=fim; i++)
  {
     x = (i+0.5)*step;
     sum_parcial = sum_parcial + 4.0/(1.0+x*x);
  }
  pthread_mutex_lock (&mutexpi);
  sum = sum_parcial + sum;
  pthread_mutex_unlock (&mutexpi);
  pthread_exit((void*) 0);

}

int main ()
{
	double pi;
	int i;
	void *status;
	pthread_attr_t attr;

	pthread_mutex_init(&mutexpi, NULL);

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	step = 1.0/(double) num_steps;

	for(i=0; i<NUM_THREADS; i++)
	{
		pthread_create(&callThd[i], &attr, calpi, (void *)i);
	  }

	pthread_attr_destroy(&attr);


	/* Wait on the other threads */
	for(i=0; i<NUM_THREADS; i++)
	{
		pthread_join(callThd[i], &status);
	}

	printf("sum %lf e step %lf\n", sum,step);
	pi = step * sum;

	printf("Valor de pi: %.30f\n", pi);
	pthread_mutex_destroy(&mutexpi);
	pthread_exit(NULL);
	return 0;
}
