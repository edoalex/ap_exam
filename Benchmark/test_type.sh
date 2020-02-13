c++ benchmark_type.cpp -o benchmark_type.x -std=c++14 -Wall -Wextra -I ../include -O3 -march=native

echo > dat.dat
./benchmark_type.x >> dat.dat
