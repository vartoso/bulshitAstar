CC=gcc
dep=Astar.c

astar: $(dep)
	$(CC) -o Astar $(dep)

clean:
	rm -y Astar
