CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -pedantic
LIBFLAGS = -lcurl -lpugixml

SRC=$(wildcard *.cpp)
OBJSRC=src/date.o src/anime.o src/xml_process.o src/mal_interface.o src/hide_input.o src/data_process.o src/main.o 
OBJ=date.o anime.o xml_process.o mal_interface.o hide_input.o data_process.o main.o

all: $(OBJSRC)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LIBFLAGS) -o main 

%.o: %.cpp
	$(CXX) $(CXXFLAGS)  $< $(LIBFLAGS) -c

clean:
	rm -f *.o*
