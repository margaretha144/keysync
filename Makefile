test: keyboard.o main.o
	gcc -o out keyboard.o main.o

keyboard.o: keyboard.h keyboard.c

main.o: keyboard.h main.c

.PHONY : clean
clean :
	-rm keyboard.o main.o out


