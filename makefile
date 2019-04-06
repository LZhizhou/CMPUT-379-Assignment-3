all: valtlb379.c
	gcc -Wall -std=c99 -c node.c
	gcc -Wall -std=c99 -c valtlb379.c
	gcc -Wall -std=c99 -o valtlb379 valtlb379.o node.o
	
clean:
	rm -rf valtlb379 *.o