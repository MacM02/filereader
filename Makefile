CC = g++
INC = include
SRC = source
GFLAGS = -Wall 

main: fileReader.o main.o
	$(CC) $(GFLAGS)

main.o: main.cpp
	$(CC) $(GFLAGS) -I$(INC) -c $(SRC)/main.cpp

fileReader.o: $(SRC)/fileReader.cpp $(INC)/fileReader.h
	$(CC) $(GFLAGS) -I$(INC) -c $(SRC)/fileReader.cpp

clean:
	rm -f main ~.o *~