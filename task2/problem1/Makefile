
CFLAGS := -Wall -Wextra -pedantic -std=c99 -D_GNU_SOURCE -D_BSD_SOURCE

all: fork-thread run

fork-thread: fork-thread.c
	$(CC) $(CFLAGS) $^ -o $@ -lrt -pthread

clean:
	$(RM) *.o fork-thread

run:
	@echo "\n\nfork thread running with only 1 fork and 1 thread"
	./fork-thread 1
	@echo "\n\nfork thread running with 10 forks and 10 threads"
	./fork-thread 10
	@echo "\n\nfork thread running with 100 forks and 100 threads"
	./fork-thread 100
	@echo "\n\n"
