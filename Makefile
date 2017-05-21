CC = gcc
all:out
out:main.c sort.c
	$(CC) main.c sort.c -o out
clean:
	-rm out