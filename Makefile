all: libinfixrpnconv.a

libinfixrpnconv.a: infixrpnconv.o stackstring.o
	ar rcs libinfixrpnconv.a infixrpnconv.o stackstring.o

infixrpnconv.o: ./src/infixrpnconv.c ./src/infixrpnconv.h ./src/stackstring.h
	gcc -c -g -Wall -Wextra -std=c99 -I./src ./src/infixrpnconv.c -o infixrpnconv.o

stackstring.o: ./src/stackstring.c ./src/stackstring.h
	gcc -c -g -Wall -Wextra -std=c99 -I./src ./src/stackstring.c -o stackstring.o

test: ./tests/check_infixrpnconv.c libinfixrpnconv.a ./src/infixrpnconv.h
	gcc -static -g -Wall -Wextra -std=c99 -I./src ./tests/check_infixrpnconv.c -lcheck -L. -linfixrpnconv -o infixrpnkatatests
	./infixrpnkatatests

clean:
	rm *.o
