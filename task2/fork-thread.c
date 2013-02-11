#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

#include <pthread.h>

//bums
/* Dummy function spawned by every thread/process.  */
int dummy (void *data)
{
    return 0;
}

/* Time difference between a and b in microseconds.  */
int64_t xelapsed (struct timespec a, struct timespec b)
{
    return ((int64_t)a.tv_sec - b.tv_sec) * 1000000
           + ((int64_t)a.tv_nsec - b.tv_nsec) / 1000LL;
}

/* Measure the time for NUMBER fork creations.  */
void measure_forks (unsigned number)
{
    struct timespec start, stop, finish;
    unsigned i = 0;
    int pid [number];
    int cur_pid;

    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 0;i < number; i++) {
		
		cur_pid = fork();
		
		switch(cur_pid)
		{
			case 0:
				dummy(NULL);
				pid[number] = cur_pid;
			case 1:
				exit(0);
		}
        /* TODO Call FORK,
                execute DUMMY in a child,
                save process id.  */
    }
    clock_gettime(CLOCK_REALTIME, &stop);

    for (i = 0; i < number; i++) {
		
		wait(&pid[number]);
		
        /* TODO Wait for every process id
                spawned in the previous loop.  */
    }
    clock_gettime(CLOCK_REALTIME, &finish);

    printf ("process: num=%03u, fork=%03li, wait=%03li, totatl=%03li\n",
            number, xelapsed (stop, start), xelapsed (finish, stop),
            xelapsed (finish, start));
}

/* Measure the time for NUMBER thread creations.  */
void measure_threads (unsigned number)
{
    /* TODO Modify MEASURE_FORKS, replacing FORK
            with thread creation and WAIT with
            thread join.  */
    struct timespec start, stop, finish;
    unsigned i = 0;
    int thread;
    pthread_t tid [number];
    pthread_t cur_tid;

    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 0;i < number; i++) 
    {
		
		thread = pthread_create(&cur_tid, NULL, dummy, NULL);
		if(thread != 0)
		{
			puts("Thread could not be created");
		}
		tid[number] = cur_tid;
		
	}
    
    clock_gettime(CLOCK_REALTIME, &stop);

    for (i = 0; i < number; i++) {
		
		pthread_join(tid[number], NULL);
		
    }
    clock_gettime(CLOCK_REALTIME, &finish);

    printf ("process: num=%03u, fork=%03li, wait=%03li, totatl=%03li\n",
            number, xelapsed (stop, start), xelapsed (finish, stop),
            xelapsed (finish, start));        
    
}


int
main (int argc, char *argv[])
{
    /* TODO Get a number of instances from the argument list
       TODO Check that the arguments are valid
       TODO Replace the argument in the subsequent function calls.  */
    
    measure_forks (atoi(argv[1]));
    measure_threads (atoi(argv[1]));
    return EXIT_SUCCESS;
}