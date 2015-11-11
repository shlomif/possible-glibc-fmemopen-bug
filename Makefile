all: a.out

a.out: test-w-calls.c
	gcc -g $<

test: a.out
	prove t/*.t
