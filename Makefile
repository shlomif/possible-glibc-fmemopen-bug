all: a.out

a.out: test-w-calls.c calls.c
	gcc -o $@ -g $<

test: a.out
	prove t/*.t

clean:
	rm -f a.out
