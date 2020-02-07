CXX = c++
CXXFLAGS = -std=c++14 -Wall -Wextra -I include/

SRC = src/bst.cpp main.cpp
OBJ = $(SRC:.cpp=.o)

all:
	 c++ main.cpp -o exe.x -std=c++14 -I include -Wall -Wextra

#exe.x: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

%.o:%.cc
	$(CXX) $< -o $@ -c $(CXXFLAGS)

main.o: main.cpp

src/bst.o: src/bst.cpp include/bst.hpp

format: $(SRC) include/bst.hpp
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"

clean:
	@rm -f *~ */*~ exe.x src/*.o *.o

.PHONY: clean all format
