CC = gcc
CFLAG = -w -x c
OBJECTS = objs\test.o objs\ins.o objs\ram.o

vm : $(OBJECTS)
	$(CC) -o vm $(OBJECTS)

objs\test.o : device\cpu.h test.c
	$(CC) $(CFLAG) -c test.c -o objs\test.o

objs\ins.o : device\ram.h device\cpu.h device\ins.h
	$(CC) $(CFLAG) -c device\ins.c -o objs\ins.o

objs\ram.o : device\ram.h device\ram.c
	$(CC) $(CFLAG) -c device\ram.c -o objs\ram.o