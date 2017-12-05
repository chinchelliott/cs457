OBJS = myNoSQL.o scanner.o
OOPTS = -Wall -Wextra -g -std=c99 -c
LOPTS = -Wall -Wextra -g -std=c99

all: nosql

nosql: $(OBJS)
	gcc $(LOPTS) -o nosql $(OBJS)

myNoSQL.o: myNoSQL.c scanner.h
	gcc $(OOPTS) myNoSQL.c

scanner.o: scanner.c scanner.h
	gcc $(OOPTS) scanner.c

clean:
	rm -f $(OBJS) nosql

test:
	./nosql data.txt queries.txt
