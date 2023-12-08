all: main

main ./src/hash.c ./src/bloom.c ./src/main.c ./src/tests.c: 
	gcc -Wall -g ./src/hash.c ./src/bloom.c ./src/main.c -lm -o ./bin/main
	gcc -Wall -g ./src/hash.c ./src/bloom.c ./src/tests.c -lm -o ./bin/tests
