#include"bst_prova.hpp"
#include<iostream>

int main(){

    bst<int, int> tree{};
    tree.insert({6,2});
    tree.insert({1,3});
    std::cout << tree << std::endl;
  return 0;
}
