OBJS = myNoSQL.o scanner.o field.o document.o sll.o
OOPTS = -Wall -Wextra -g -std=c99 -c
LOPTS = -Wall -Wextra -g -std=c99

all: nosql

nosql: $(OBJS)
	gcc $(LOPTS) -o nosql $(OBJS)

myNoSQL.o: myNoSQL.c scanner.h field.h document.h
	gcc $(OOPTS) myNoSQL.c

scanner.o: scanner.c scanner.h
	gcc $(OOPTS) scanner.c

field.o: field.c field.h
	gcc $(OOPTS) field.c

sll.o: sll.c sll.h
	gcc $(OOPTS) sll.c

document.o : document.c document.h sll.h field.h
	gcc $(OOPTS) document.c

clean:
	rm -f $(OBJS) nosql

test:
	./nosql data.txt queries.txt
