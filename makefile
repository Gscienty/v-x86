CC = gcc
CFLAG = -w -x c
OBJECTS = objs\test.o objs\ins_util.o objs\ram.o objs\port.o objs\ins.part1.o objs\ins.part2.o objs\ins.part3.o

vm : $(OBJECTS)
	$(CC) -o vm $(OBJECTS)

objs\test.o : 
	$(CC) $(CFLAG) -c test.c -o objs\test.o

objs\ins_util.o : 
	$(CC) $(CFLAG) -c device\ins\util.c -o objs\ins_util.o

objs\ins.part1.o : 
	$(CC) $(CFLAG) -c device\ins\a-b.c -o objs\ins.part1.o

objs\ins.part2.o : 
	$(CC) $(CFLAG) -c device\ins\c-d.c -o objs\ins.part2.o

objs\ins.part3.o : 
	$(CC) $(CFLAG) -c device\ins\h-i.c -o objs\ins.part3.o

objs\ram.o : 
	$(CC) $(CFLAG) -c device\ram.c -o objs\ram.o

objs\port.o : 
	$(CC) $(CFLAG) -c device\port.c -o objs\port.o

clear :
	rm $(OBJECTS)