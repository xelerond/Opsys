

CFLAGS := -Wall -Wextra -pedantic -std=c99 -D_GNU_SOURCE -D_BSD_SOURCE

array-join: barrier.c
	$(CC) $(CFLAGS) $^ -o $@ -lrt -pthread

clean:
	$(RM) *.o array-join
