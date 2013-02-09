/*
 * daemoon.c
 * 
 * Copyright 2013 Jonathan James Menzies <jm333@linux61>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main(int argc, char **argv)
{
	
	pid_t pid, sid;
	time_t time_r;
	struct tm * ptr_time;
	
	pid = fork();
	
	if(pid < 0){
		
		exit(EXIT_FAILURE);
		
	}
	
	if(pid > 0){
		
		exit(EXIT_SUCCESS);
	}
		
	
	umask(0);	
	
	openlog("timestamp2",0,0);
	
	sid = setsid();
	
	if(sid < 0){
		
		exit(EXIT_FAILURE);
		
	}
	
	if ((chdir("/")) < 0) {
                
         exit(EXIT_FAILURE);
       
    }
    
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    while(1){
		time ( &time_r );
	    ptr_time = localtime ( &time_r );
		syslog(LOG_INFO,"Current local time and date : %s",asctime(ptr_time));
		printf("Current local time and date: %s", asctime(ptr_time));
		sleep(10);
	}
	exit(EXIT_SUCCESS);
	closelog();
}

