all: test.c structs.c main.c
	gcc test.c -o test
	gcc main.c -o main

test: test.c structs.c
	gcc test.c -o test

main: main.c structs.c
	gcc main.c -o main

clean:
	rm test
	rm main
