CC=g++
OPT=-Og

hello: helloworld.c
	$(CC) $(OPT) $^ -o hello

gradient: vector.h ray.h gradient.cpp
	$(CC) $(OPT) $^ -o gradient

tests: vector.h ray.h tests.cpp
	$(CC) $(OPT) $^ -o tests

.PHONY: clean
clean:
	rm -rf ./*.o ./*.gch ./*.out ./*.ppm hello gradient tests