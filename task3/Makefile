IN := super_malloc.c testpart3.c
OUT := test-malloc

all: compile run clean

compile: super_malloc.c testpart3.c
	$(CC) -o $(OUT) $(IN)

run:
	@echo "running malloc test file\n-\n-\n-\n-"
	./$(OUT)
	@echo "-\n-\n-\n-\ncompleted running"

clean:
	$(RM) *.o $(OUT)
