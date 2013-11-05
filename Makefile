OBJS = main.o algorithm.o
CC = g++

isvedimas: $(OBJS)
	$(CC) $(OBJS) -o isvedimas
main.o: main.cpp 
	$(CC) -g -c main.cpp
algorithm.o: algorithm.cpp 
	$(CC) -g -c algorithm.cpp
clean:
	\rm *.o *~ kodavimas