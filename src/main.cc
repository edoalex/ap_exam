#include<bst.hpp>

int main(){

  bst tree{};

  tree.insert({4,5});
  tree.insert({9,5});
  tree.insert({3,7});

  std::cout << bst << std::endl; 
  
  return 0;
  
}
