CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic
BIN=spel

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	$(CXX) -o $(BIN) $^ -lncurses # $^ all .cpp

run: all
	./spel

%.o: %.c
	$(CXX) $@ -c $< -lncurses # $< first .cpp

clean: 
	rm -f *.o
	rm -rf *.dSYM/
	rm $(BIN)