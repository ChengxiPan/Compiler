test:prog.o code.o
	gcc prog.o -o ./output
prog.o:prog.cpp
	gcc -c prog.cpp -o prog.o
clean:
	rm -f *.o test