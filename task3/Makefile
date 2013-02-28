IN := super_malloc.c testpart3.c
OUT := test-malloc

all: test-malloc run clean

test-malloc: super_malloc.c testpart3.c
	$(CC) -o $(OUT) $(IN)

run:
	@echo "running malloc test file"
	./$(OUT)

clean:
	$(RM) *.o $(OUT)
