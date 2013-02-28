
CFLAGS :=

all: test-malloc run clean

test-malloc: super_malloc.c testpart3.c
	$(CC) $(CFLAGS) $^ -o $@

run: $@echo "running malloc test file"
	$(./test-malloc)

clean:
	$(RM) *.o test-malloc
