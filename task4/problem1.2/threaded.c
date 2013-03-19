#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define N_THREADS 16
#define SIZE 1000
#define ITERATIONS 100000

#define MIN( a, b)  ((a)<(b)? (a): (b))

//structure of time data from lab 2 fork-thread
struct timespec start, stop, finish;

//from lab sheet - structure of thread info i beleive
typedef struct threadArgs threadArgs_t;
threadArgs_t ** t ;

struct threadArgs {
  pthread_t tid;
  int from;
  int to;
};

//declare arrays
double a[SIZE];
double b[SIZE];

pthread_barrier_t barrier;

//function given in lab exercise 2 from fork-thread
// Time difference between a and b in microseconds.
int64_t xelapsed (struct timespec a, struct timespec b)
{
    return ((int64_t)a.tv_sec - b.tv_sec) * 1000000
           + ((int64_t)a.tv_nsec - b.tv_nsec) / 1000LL;
}

//initialise data in 2 arrays
void initData( )
{
  //one array counts up to size, one counts down from
  //will mean elements when added will all be size -1
  int i;
  for( i=0; i<SIZE; i++) {
    a[i] = i;
    b[i] = (SIZE-1) - i;
  }
  //not needed in this part, but will help keep time values the same
  pthread_barrier_init( &barrier, NULL, N_THREADS);
}

//sequential element-wise addition of array
void sequential()
{
  //for each iteration up until specified number of iterations...
  int iteration = 0;
  for(iteration = 0; iteration < ITERATIONS; iteration++)
  {
    //not sure if initdata needed on every iteration?
    //initData();

    //for each element of arrays...
    int i = 0;
    for(i = 0; i < SIZE; i++)
    {
      //the current elemtn of a = itself plus current element in b
      a[i] = a[i] + b[i];
    }
  }
}

void * simd(void *arg)
{
  puts("im here");
  int tid,from,to;
  
  //struct threadArg * ta = (struct threadArg *) arg;
  
  tid = ((threadArgs_t *)arg)->tid;
  from = ((threadArgs_t *)arg)->from;
  printf("%d\n",from);
  to = ((threadArgs_t *)arg)->to;
  
  printf("%d\n",to);
  int g;
  for(g = 0; g <= 1;g++)
  { 
	  puts("josh don't like cricket");
	  int i = 0;
	  for (i = 0; i< 10; i++)
	  {
		a[i] = a[i] + b[i];
		
	  }
  }
  puts("le cake");
  return 0;
}

//not sure if this is needed, but here you go mr john
void threaded (int numThreads)
{
	int z = 0;
	t = malloc(numThreads*sizeof(threadArgs_t *));
	for(z = 0; z < numThreads;z++)
	{
		t[z] = malloc(sizeof(threadArgs_t ));
	}
	int thread;
	int i,j = 0;
	//thread id array
    //id of current thread
    int threadsize = (SIZE/numThreads);
    //printf("%d",threadsize);
    
		for (i = 0;i < numThreads; i++) 
		{
			pthread_t tid;
			t[i]->from = threadsize * i;
			t[i]->to = t[i]->from + threadsize;
			t[i]->tid = tid;
			printf("from:- %d to:- %d",t[i]->from,t[i]->to);	
			//create a thread and store success value of creation
			//also runs dummy inside thread
			puts("id this running?");
			thread = pthread_create(&tid, NULL, simd, (void *)t[i]);
			//printf("%d\n",from);
			// printf("%d\n",to);
			puts("success");
			//outputs error of thread failure
			if(thread > 0)
			{
				puts("Thread could not be created");
			}
			//stores current thread id
			
		}
		for(j = 0; j < numThreads;j++)
		{
			if((pthread_join(t[j]->tid,NULL) != 0))
			{
				puts("failed to join");
			}
			else
				puts("shawaz");
		}
		
}

int main()
{
  //save time of start in time struct
  clock_gettime(CLOCK_REALTIME, &start);

  //intialise array data
  initData();
  //run sequential addition
  threaded(1);

  //save time clock was stopped
  clock_gettime(CLOCK_REALTIME, &stop);

  //print time difference between start and stop in microseconds
  printf ("run time for sequential=%03li\n",
            xelapsed (stop, start));

  //stops angry compiler messages
  return 0;
}

  

