OBJS = myNoSQL.o scanner.o field.o document.o sll.o collection.o bst.o queue.o rbt.o querybuilder.o
OOPTS = -Wall -Wextra -g -std=c99 -c
LOPTS = -Wall -Wextra -g -std=c99

all: nosql

nosql: $(OBJS)
	gcc $(LOPTS) -o nosql $(OBJS)

myNoSQL.o: myNoSQL.c scanner.h field.h document.h collection.o queue.h bst.h rbt.h querybuilder.h
	gcc $(OOPTS) myNoSQL.c

scanner.o: scanner.c scanner.h
	gcc $(OOPTS) scanner.c

field.o: field.c field.h
	gcc $(OOPTS) field.c

sll.o: sll.c sll.h field.h
	gcc $(OOPTS) sll.c

document.o : document.c document.h sll.h field.h queue.h
	gcc $(OOPTS) document.c

queue.o: queue.c queue.h sll.h
	gcc $(OOPTS) queue.c

bst.o: bst.c bst.h queue.h
	gcc $(OOPTS) bst.c

rbt.o: rbt.c rbt.h bst.h queue.h
	gcc $(OOPTS) rbt.c

collection.o: collection.c collection.h rbt.h document.h queue.h
	gcc $(OOPTS) collection.c

querybuilder.o : querybuilder.c querybuilder.h collection.h document.h field.h queue.h
	gcc $(OOPTS) querybuilder.c

clean:
	rm -f $(OBJS) nosql

test:
	./nosql data.txt queries.txt

lldb_test:
	./nosql data.txt queries.txt
