CXX = c++
CXXFLAGS = -std=c++14 -Wall -Wextra -I include/

SRC = src/bst.cpp main.cpp
OBJ = $(SRC:.cpp=.o)

all:
	 c++ main.cpp -o exe.x -std=c++14 -I include -Wall -Wextra -g