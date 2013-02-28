//Robbie Henderson - H00011358

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
  //if not correct arguments
  if (argc<2)
  {
    //explain usage and exit
    puts("usage - pattern to find, file, file, file, more files");
    exit(0);
  }
  //counter for loop
	int counter;
  //for each argument that is a file
	for (counter = 2; counter < argc; counter ++)
	{
    //used to stor position
		int pos =0;
		//if the file doe not exist
		if(!fopen(argv[counter], "r"))
		{
      //error message
			printf("file '%s' was not found\n", argv[counter]);
		}
    //if the pattern is not in the file
		else if (-1 == (pos=search(fopen (argv[counter], "r"), argv[1])))
    {
      //print not found in file
			printf ("pattern '%s' was not found in %s\n",argv[1], argv[counter]);
		} 
    //otherwise
		else
    {
      //print position string was found in file
			printf ("pattern '%s' found in %s at position %d\n", argv[1],argv[counter], pos);
		}
	}
	return EXIT_SUCCESS;
}