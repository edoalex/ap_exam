CXX = c++
CXXFLAGS = -std=c++14 -Wall -Wextra -I include -O3
DEP = include/bst.hpp include/bst_functions.hpp include/node.hpp include/iterator.hpp include/ap_error.h

all: exe.x docs

exe.x: $(DEP)
	$(CXX) main.cpp -o $@ $(CXXFLAGS)

docs: $(DEP)
	doxygen

clean:
	@rm -f *~ */*~ exe.x


.PHONY: clean all format
