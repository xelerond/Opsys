#include <syslog.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

void printtime()
{
	time_t t;
		struct tm *lat;
		t = time(NULL);
		lat = localtime(&t);
		openlog ("time program", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
		syslog(LOG_INFO, "Local time is : %s", asctime(lat));
		printf("Local time is : %s \n", asctime(lat));
		closelog();
}

void timedprint()
{
	int cake = 0;
	while (cake<1000)
	{
		sleep(10);
		printtime();
		cake ++;
	}
}

int main(void)
{
	timedprint();
	return(0);
}
