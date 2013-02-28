

all: search run

fork-thread: gcc -o search search.c

clean:
	$(RM) *.o search

run:
	@echo "\nrun to find test which is located in both files"
	./search test test.txt test2.txt
	@echo "\nrun to find cake which is located in test.txt only"
	./search cake test.txt test2.txt
	@echo "\nrun to find albatross which is located in test2.txt only\n"
	./search albatross test.txt test2.txt