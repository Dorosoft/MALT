CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -pedantic
LIBFLAGS = -lcurl -lpugixml

SRC=$(wildcard *.cpp)
OBJ=date.o anime.o xml_process.o mal_interface.o data_process.o hide_input.o main.o 

all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LIBFLAGS) -o main 

%.o: %.cpp
	$(CXX) $(CXXFLAGS)  $< $(LIBFLAGS) -c

clean:
	rm -f *.o*
