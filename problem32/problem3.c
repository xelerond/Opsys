#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

void bufferiser(int fd)
{
    char* buf = NULL;
    char* bufp;
    size_t bufsz, cursz, curpos;
    ssize_t ssz;
    struct stat st;
    /* Assuming that FD is a file descriptor opened for
    reading, get file system I/O blocksize into BUFSZ. */
    if (fstat (fd, &st) >= 0) {
    bufsz = (size_t) st.st_blksize;
    } else {
        puts("HELLO");
    /* Handle error. */
    }
    /* Allocate buffer of size BUFSZ. */
    buf = (char *) malloc (bufsz);
    curpos = 0;
    cursz = bufsz;
    /* Block read FD, storing data into BUF. */
    while ((ssz = read (fd, buf + curpos, bufsz)) > 0) {
    curpos += ssz;
    cursz = curpos + bufsz;
    if (NULL == (bufp = (char *) realloc (buf, cursz))) {
    /* Handle error. */
    }
    buf = bufp;
    }
    /* Zero-terminate BUF. */
    buf[curpos] = 0;

    


    puts(buf);
}


int main(int argc, char * argv[])
{
    int pid;
    pid = fork();
    int fd[2];
    pipe(fd);
    
    switch(pid)
    {
        case -1:
        {
            perror("fork error");
            exit(1);
            break;
        }
        case 0:
        {
            close(fd[0]);
            close(0);
            dup2(fd[1],0);
            execv("/bin/ls", argv);
            break;
        }
        default:
        {
            wait(&pid);
            close(fd[1]);
            close(1);
            bufferiser(fd[0]);
            break;
        }
    }
    return 0;
}