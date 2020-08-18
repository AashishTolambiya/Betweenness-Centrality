a.out : 3_main.o 3_impl.o
	gcc 3_main.o 3_impl.o -lncurses

3_main.o: 3_main.c 3_header.h
	gcc -c 3_main.c -lncurses

3_impl.o : 3_impl.c 3_header.h
	gcc -c 3_impl.c -lncurses

