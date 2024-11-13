EXEC=p1_exec

CC=g++
CFLAGS=-std=c++98 -I.


%.o: %.cpp
	$(CC) -c $< $(CFLAGS)


${EXEC}: main.o p1_process.o p1_threads.o Merge_Two_SortedLists.o 
	g++ -o ${EXEC} main.o p1_process.o p1_threads.o Merge_Two_SortedLists.o  -I. -lpthread 

clean:
	rm -rf ./${EXEC}
	rm -rf ./*.o
	rm -rf ./output/*.csv

