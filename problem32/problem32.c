#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>

//function provided by Bodo on lab sheet
char* bufferiser(int fd)
{
    char* buf = NULL;
    char* bufp;
    size_t bufsz, cursz, curpos;
    ssize_t ssz;
    struct stat st;
    /* Assuming that FD is a file descriptor opened for
    reading, get file system I/O blocksize into BUFSZ. */
    
    if (fstat (fd, &st) >= 0)
    {
        bufsz = (size_t) st.st_blksize;
    }
    
    else
    {
        puts("HELLO");
        /* Handle error. */
    }
    /* Allocate buffer of size BUFSZ. */
    buf = (char *) malloc (bufsz);
    curpos = 0;
    cursz = bufsz;
    /* Block read FD, storing data into BUF. */
    while ((ssz = read (fd, buf + curpos, bufsz)) > 0)
    {
        curpos += ssz;
        cursz = curpos + bufsz;
        if (NULL == (bufp = (char *) realloc (buf, cursz)))
        {
            /* Handle error. */
        }
        buf = bufp;
    }
    /* Zero-terminate BUF. */
    buf[curpos] = 0;
    return(buf);
}

int fileCount(char* lsReturn, int max)
{
    char current = lsReturn[0];
    int i = 0;
    int files = 0;
    
    while(files <= max +2)
    {
        if (current == '\n')
            files++;
        else if (current == '\0')
            return files;
        i++;
        current = lsReturn[i];
    }
    if (files > max)
        return max+2;
    else
        return files;
    
    return 0;
}


int main(int argc, char** argv)
{
    int max = 25;
    int fd[2];
    char* buffer;
    int pid;
    pipe(fd);      
    pid = fork();

    switch(pid)
        {
        case 0:
            close(fd[0]);
            close(1);
            dup2(fd[1],1);
            execv("/bin/ls", argv);
        break;

        case -1:
            printf("FAILED");
        break;

        default:
            wait(&pid);
            close(fd[1]);
            close(0);
            buffer = bufferiser(fd[0]);
            if(fileCount(buffer, max)<max+1)
            {
                puts(buffer);
            }
            else
            {
                puts("too many files");
            }
        break;
    }
    return EXIT_SUCCESS;
}