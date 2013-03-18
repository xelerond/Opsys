

CFLAGS := -Wall -Wextra -pedantic -std=c99 -D_GNU_SOURCE -D_BSD_SOURCE

array-join: threaded.c
	$(CC) $(CFLAGS) $^ -o $@ -lrt -pthread

run:
	./array-join

clean:
	$(RM) *.o array-join
