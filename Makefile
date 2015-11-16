project: main.o split.o function.o merge.o 
	gcc split.o function.o main.o merge.o -o project
main.o : main.c configuration.h function.h split.h extra.h merge.h
	gcc -c -Wall main.c
split.o: split.c configuration.h function.h split.h extra.h merge.h
	gcc split.c -c -Wall
merge.o: split.c configuration.h function.h split.h extra.h merge.h
	gcc merge.c -c -Wall
function.o: function.c main.c configuration.h function.h extra.h merge.h
	gcc function.c -c -Wall
