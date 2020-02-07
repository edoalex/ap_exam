#include"bst_prova.hpp"
#include<iostream>
#include<functional>

int main(){

  bst<const int,int,std::less<const int>> tree{};

  tree.insert(std::make_pair<const int,int>(4,5));
  //tree.insert({5,5});
  //tree.insert({7,9});

  std::cout << tree << std::endl;
  
  return 0;
  
}
