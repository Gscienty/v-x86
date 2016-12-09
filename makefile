CC = gcc
CFLAG = -x c
OBJECTS = objs\test.o objs\ins.o

vm : $(OBJECTS)
	$(CC) -o vm $(OBJECTS)

objs\test.o : device\cpu.h test.c
	$(CC) -c test.c -o objs\test.o

objs\ins.o : device\cpu.h device\ins.h device\ins.c
	$(CC) -c device\ins.c -o objs\ins.o