#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <inttypes.h>

#define N_THREADS 16
#define SIZE 1000
//set iterations higher as result time was too small
#define ITERATIONS 1

#define MIN( a, b)  ((a)<(b)? (a): (b))

//structure of time data from lab 2 fork-thread
struct timespec start, stop, finish;

//from lab sheet - structure of thread info i beleive
typedef struct threadArgs threadArgs_t;
threadArgs_t ** t ;

//struct that will store thread it and the start/end position of the threads
struct threadArgs {
  pthread_t tid;
  int from;
  int to;
};

//declare arrays
double a[SIZE];
double b[SIZE];

//only needed for part 4
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

//parralell adition
void * simd(void *arg)
{
  //data taken out of struct
  int tid,from,to;
  tid = (intptr_t)((threadArgs_t *)arg)->tid;
  from = ((threadArgs_t *)arg)->from;
  to = ((threadArgs_t *)arg)->to;

  //simple counter
  int g=0;

  //run one addition 'ITERATIONS' times
  for(g = 0; g <= ITERATIONS;g++)
  {
    //carry out single array addition
    //essentially the same as in sequential
    int i = 0;
    for (i = from; i<= to; i++)
    {
      a[i] = a[i] + b[i];
    }
  }
  //happy compiler = happy me
  return 0;
}

//initialise threaded addition
void threaded (int numThreads)
{
  //not used z as counter yet, z is nice
  int z = 0;

  //allocate memory for struct of thread info
  t = malloc(numThreads*sizeof(threadArgs_t *));

  //allocate array of structs memory for the number of threads used
  for(z = 0; z < numThreads;z++)
  {
    t[z] = malloc(sizeof(threadArgs_t ));
  }

  //calculate size of array each thread will deal with
  //+1 compensates for rounding down
  int i,j = 0;
  int threadsize = (SIZE/numThreads) + 1;

    //for each thread....
    for (i = 0;i < numThreads; i++) 
    {
      //get the start position for thread
      t[i]->from = threadsize * i;
      //calculate end position and change if too big
      t[i]->to = t[i]->from + threadsize;
      if(t[i]->to > SIZE)
        t[i]->to = SIZE;

      //create thread and store success value
      int return_status = pthread_create(&(t[i]->tid), NULL, simd, (void *)t[i]);

      //outputs error if thread creation failed
      if(return_status != 0)
      {
        puts("Thread could not be created");
        //return error status of thread join
        exit(return_status);
      }
      
    }

    //for each thread created
    for(j = 0; j < numThreads;j++)
    {
      //wait for thread to comeplete execution
      int return_status = (pthread_join(t[j]->tid,NULL));
      //if joining not successfull, error message to user and exit
      if(return_status != 0)
      {
        puts("failed to join");
        
      }
    }
    
}

//main
int main(int argc, char * argv[])
{
  //validates input from terminal
  if (argc != 2 || atoi(argv[1])<=0 || atoi(argv[1]) > 30)
  {
    puts("input number between 1 and 30 - inclusive");
    exit(0);
  }

  //save time of start in time struct
  clock_gettime(CLOCK_REALTIME, &start);

  //intialise array data
  initData();
  //run parallel addition
  threaded(atoi(argv[1]));

  //save time clock was stopped
  clock_gettime(CLOCK_REALTIME, &stop);

  //print time difference between start and stop in microseconds
  printf ("run time for parallel= %" PRId64 "\n",xelapsed (stop, start));

  //save time of start in time struct
  clock_gettime(CLOCK_REALTIME, &start);
  
  //intialise array data
  initData();
  //run sequential addition
  sequential();

  //save time clock was stopped
  clock_gettime(CLOCK_REALTIME, &stop);
  
  //print time difference between start and stop in microseconds
  printf ("run time for sequential= %" PRId64 "\n",xelapsed (stop, start));

  //stops angry compiler messages because of int main
  return EXIT_SUCCESS;
}

  

