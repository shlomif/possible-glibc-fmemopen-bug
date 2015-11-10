all: a.out

a.out: test-w-calls.c
	gcc -g $<
