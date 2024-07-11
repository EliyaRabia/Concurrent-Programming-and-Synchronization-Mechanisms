CXX = g++
CXXFLAGS = -std=c++17 -pthread

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

all: ex3.out

ex3.out: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o ex3.out