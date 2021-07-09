build:
	gcc -Wextra -Wall -g *.c -o tema2

test: build
	valgrind --leak-check=full ./tema2

clean:
	rm tema2 output_*