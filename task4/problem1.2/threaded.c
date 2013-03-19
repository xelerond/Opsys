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

struct threadArgs {
  int tid;
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

void simd( void *arg)
{
  int tid,from,to;

  tid = ((threadArgs_t *)arg)->tid;
  from = ((threadArgs_t *)arg)->from;
  to = ((threadArgs_t *)arg)->to;

  // Here, the addition happens....
}

//not sure if this is needed, but here you go mr john
void threaded ()
{

}

int main()
{
  //save time of start in time struct
  clock_gettime(CLOCK_REALTIME, &start);

  //intialise array data
  initData();
  //run sequential addition
  sequential();

  //save time clock was stopped
  clock_gettime(CLOCK_REALTIME, &stop);

  //print time difference between start and stop in microseconds
  printf ("run time for sequential=%03li\n",
            xelapsed (stop, start));

  //stops angry compiler messages
  return 0;
}

  

