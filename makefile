nanoXML.exe : t_element.o main.o
	gcc -o nanoXML.exe t_element.o main.o

t_element.o : t_element.c t_element.h
	gcc -c t_element.c

main.o : main.c
	gcc -c main.c

clean:
	rm *.o
	rm *.exe