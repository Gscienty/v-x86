CC = gcc
CFLAG = -w -x c
OBJECTS = objs\test.o objs\ins_util.o objs\ram.o objs\ins_a_b.o

vm : $(OBJECTS)
	$(CC) -o vm $(OBJECTS)

objs\test.o : device\cpu.h test.c
	$(CC) $(CFLAG) -c test.c -o objs\test.o

objs\ins_util.o : device\ram.h device\cpu.h device\ins.h
	$(CC) $(CFLAG) -c device\ins\util.c -o objs\ins_util.o

objs\ins_a_b.o : device\ram.h device\cpu.h device\ins.h
	$(CC) $(CFLAG) -c device\ins\a-b.c -o objs\ins_a_b.o

objs\ins_c.o : device\ram.h device\cpu.h device\ins.h
	$(CC) $(CFLAG) -c device\ins\ins\c.c -o objs\ins_c.o

objs\ram.o : device\ram.h device\ram.c
	$(CC) $(CFLAG) -c device\ram.c -o objs\ram.o

clear :
	rm $(OBJECTS)