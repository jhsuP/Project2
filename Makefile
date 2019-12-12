project: user_interface.o llist.o 
	g++ user_interface.o llist.o -o project

user_interface.o: user_interface.cpp
	g++ -ansi -pedantic-errors -Wall -c user_interface.cpp -DDEBUGMODE

llist.o: llist.cpp
	g++ -ansi -pedantic-errors -Wall -c llist.cpp -DDEBUGMODE

