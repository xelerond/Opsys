#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


/* A function to searcg a substing in a file.  The file F has to be
   opened and the function is going to call subsequent fgetc on F
   until it reaches EOF or finds the match.

   Input arguments:
       F    -- input file opened for reading
       PAT  -- a pattern to be found.

   Return values:
       -1   -- in case the pattern was not found
      x > 0 -- where x is a position of the match.  */
int search (FILE *f, const char *pat)
{
    int i, j, c, pos = 1;
    const char *ptr;

    for (; EOF != (c = fgetc (f)); pos++) {
        if (c != *pat)
            continue;

        for (i = 1, ptr = pat + 1; *ptr != '\0'; i++, ptr++)
            if (*ptr != (c = fgetc (f))) {
                ungetc (c, f);
                break;
            }

        if (*ptr == '\0')
            return pos;
        else
            for (j = i - 1; j > 0; j--)
                ungetc (pat[j], f);
    }

    return -1;
}


void forkfind(int counter, char*arguments[])
{
	printf("fork searching %s\n", arguments[counter]);
	int pos =0;
	if(!fopen(arguments[counter], "r"))
	{
		printf("file '%s' was not found\n", arguments[counter]);
	}
	else if (-1 == (pos=search(fopen (arguments[counter], "r"), arguments[1]))) {
		printf ("pattern '%s' was not found in %s\n",arguments[1], arguments[counter]);
	} 
	else {
		printf ("pattern '%s' found in %s at position %d\n", arguments[1],arguments[counter], pos);
	}
}

/* done TODO: Check if the arguments are valid
   done TODO: Todo, open the file safely
   done TODO: Execute SEARCH for every file in ARGV
   done TODO: Print the position found
   done TODO: Make sure it does not segfaults in case
         arguments are wrong.

   done XXX: Use a better searching algorihm.  */
int main (int argc, char *argv[])
{
	int pidarray[argc -2];
	int counter;
	for (counter = 2; counter < argc; counter ++)
	{
		int pid = fork();
		if (pid == 0)
		{
			pidarray[counter-2]= pid;
			forkfind(counter, argv);
			exit(0);
		}
	}
	for (counter = 0; counter<(argc-2); counter ++)
	{
		wait(&pidarray[counter]);
	}
	return EXIT_SUCCESS;
}
