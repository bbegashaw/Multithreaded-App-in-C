all:
	cc thread3520.c -lpthread
	./a.out 
clean:
	rm a.out