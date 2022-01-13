CC=gcc
RESULT=example1
OBJS=httpConnect.o example1.o
INCLUDE=-I include/

all: $(OBJS)
	gcc $(OBJS) -o $(RESULT) $(INCLUDE)

httpConnect.o:
	gcc src/httpConnect.c -c $(INCLUDE)

example1.o: 
	gcc example1.c -c $(INCLUDE)

clear:
	rm *.o -rf
