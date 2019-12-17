CC=g++
OPT=-Og

tests: vector.h ray.h tests.cpp
	$(CC) $(OPT) $^ -o tests

.PHONY: clean
clean:
	rm -rf ./*.o ./*.gch ./*.out ./*.ppm