CC=g++
all: TimeExtraction

TimeExtraction: TimeExtraction.o Helper.o Process.o Date.o
	$(CC) TimeExtraction.o Helper.o Process.o Date.o -o TimeExtraction

Process.o: Process.cpp
	$(CC) -c Process.cpp

Date.o: Date.cpp
	$(CC) -c Date.cpp

Helper.o: Helper.cpp
	$(CC) -c Helper.cpp

TimeExtraction.o: TimeExtraction.cpp
	$(CC) -c TimeExtraction.cpp

clean:
	rm -rf *o TimeExtraction
