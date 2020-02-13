c++ benchmark.cpp -o benchmark.x -std=c++14 -Wall -Wextra -I include -O3 -march=native

echo > dat.dat
./benchmark.x >> dat.dat
