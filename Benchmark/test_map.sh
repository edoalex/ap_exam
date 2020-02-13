c++ benchmark_map.cpp -o benchmark_map.x -std=c++14 -Wall -Wextra -I ../include -O3 -march=native

echo > dat.dat
./benchmark_map.x >> dat.dat
