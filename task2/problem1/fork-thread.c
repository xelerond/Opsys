#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

#include <pthread.h>

//dummy code given in lab exercise
/* Dummy function spawned by every thread/process.  */
void* dummy (void *data)//void* stopped issue with thread creation in compiler
{
	data = data;
    return 0;
}

// code given in lab exercise
/* Time difference between a and b in microseconds.  */
int64_t xelapsed (struct timespec a, struct timespec b)
{
    return ((int64_t)a.tv_sec - b.tv_sec) * 1000000
           + ((int64_t)a.tv_nsec - b.tv_nsec) / 1000LL;
}

/* Measure the time for NUMBER fork creations.  */
void measure_forks (unsigned number)
{
	//variables
	//structure to store time data
    struct timespec start, stop, finish;
    //counter
    unsigned i = 0;
    //pid array to store all forks
    int pid [number];
    //current pid of process
    int cur_pid;
    //start clock
    clock_gettime(CLOCK_REALTIME, &start);
    //for a count up to number
    for (i = 0;i < number; i++) {
		//create a new fork and store pid
		cur_pid = fork();
		//find child
		switch(cur_pid)
		{
			//in child process do -
			case 0:
				//run dummy to ensure the process does not instantly exit
				dummy(0);
				//store current process in pid array
				pid[i] = cur_pid;
				//exit child
				exit(0);
			//in parent
			case 1:
				//exit parent
				exit(0);
		}
        /* TODO Call FORK,
                execute DUMMY in a child,
                save process id.  */
    }
    //stop clock
    clock_gettime(CLOCK_REALTIME, &stop);
	//for count to number
    for (i = 0; i < number; i++) {
		//wait for the forks to finish processing
		wait(&pid[i]);
    }
    //finish clock
    clock_gettime(CLOCK_REALTIME, &finish);

    //print info about times
    printf ("process: num=%03u, fork=%03li, wait=%03li, totatl=%03li\n",
            number, xelapsed (stop, start), xelapsed (finish, stop),
            xelapsed (finish, start));
}

/* Measure the time for NUMBER thread creations.  */
void measure_threads (unsigned number)
{
    //structure for time storage
    struct timespec start, stop, finish;
    //counter
    unsigned i = 0;
    //thread success
    int thread;
    //thread id array
    pthread_t tid [number];
    //id of current thread
    pthread_t cur_tid;

    //start clock
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 0;i < number; i++) 
    {
		//create a thread and store success value of creation
		//also runs dummy inside thread
		thread = pthread_create(&cur_tid, NULL, dummy, NULL);
		//outputs error of thread failure
		if(thread != 0)
		{
			puts("Thread could not be created");
		}
		//stores current thread id
		tid[i] = cur_tid;
		
	}
    //stop clock
    clock_gettime(CLOCK_REALTIME, &stop);

    for (i = 0; i < number; i++)
    {
    	//wait for all threads to rejoin current
		pthread_join(tid[i], NULL);
    }
    //finish clock
    clock_gettime(CLOCK_REALTIME, &finish);
    //print time data
    printf ("thread: num=%u, thread=%03li, join=%03li, total=%03li\n",
            number, xelapsed (stop, start), xelapsed (finish, stop),
            xelapsed (finish, start));        
    
}


int main (int argc, char *argv[])
{
	//validates only one argument
	if (argc > 1 && argc < 3)
	{
		//validates the size of the integer input
		if (atoi(argv[1])> 0 && atoi(argv[1])<= 10000)
		{
			//calls methods to measure fork creation time
			measure_forks (atoi(argv[1]));
			//and thread creation time
			measure_threads (atoi(argv[1]));
		}
		else
			//outputs error about number being too large or small
			puts("number too large or too small");
	}
	else
	{
		//tells user that argument is required
		puts("requires argument - integer from 1 to 10000");
	}
	//end program
	return EXIT_SUCCESS;
}
