#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


int main (int argc, char *argv[])
{
	int counter;
  //loop from the second argument
	for (counter = 2; counter < argc; counter ++)
	{
		int pos =0;
		
		if(!fopen(argv[counter], "r"))
		{
			printf("file '%s' was not found\n", argv[counter]);
		}
		else if (-1 == (pos=search(fopen (argv[counter], "r"), argv[1]))) {
			printf ("pattern '%s' was not found in %s\n",argv[1], argv[counter]);
		} 
		else {
			printf ("pattern '%s' found in %s at position %d\n", argv[1],argv[counter], pos);
		}
	}
	return EXIT_SUCCESS;
}
