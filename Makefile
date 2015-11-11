all: a.out

a.out: test-w-calls.c calls.c
	gcc -D_POSIX_C_SOURCE=200809 -Wall -o $@ -g $<

test: a.out
	prove t/*.t

clean:
	rm -f a.out
