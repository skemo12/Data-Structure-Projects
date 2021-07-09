build:
	gcc -g -Wall -Wextra bnet.c -o bnet

test: build
	valgrind --leak-check=full ./main

clean:
	rm bnet 