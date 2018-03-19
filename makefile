all: test.c structs.c main.c defines.h bin_to_bcd.c
	gcc test.c -o test
	gcc main.c -o main

test: test.c structs.c defines.h bin_to_bcd.c
	gcc test.c -o test

main: main.c structs.c defines.h bin_to_bcd.c
	gcc main.c -o main

clean:
	rm test
	rm main
