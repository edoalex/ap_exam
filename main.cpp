#include"bst.hpp"
#include<iostream>

int main(){

  try {
   
    bst<int,int> tree{};
    // tree.insert({1,2});

    //bst<int,int> tree_2{};
    //std::cout << tree << std::endl;
    // tree_2 = tree;
    //tree_2.insert({1,2});
    //tree.insert({0,2});
    //std::cout << tree << std::endl;
    tree.emplace(1,2);
    std::cout << tree << std::endl;
    //throw std::runtime_error("Are there leaks?");
	
    /*
      tree.insert({8,3});
      tree.insert({8,4});
      tree.insert({10,10});
      tree.emplace(std::make_pair<int,int>(9,5),nullptr);
      tree.insert({12,12});
      tree.insert({11,11});
      tree.insert({16,15});
      tree.insert({9,9});
      tree.insert({0,1});
      tree.insert({5,2});
      tree.insert({7,1});
      tree.insert({14,14});
      tree.insert({13,13});
      tree.insert({15,15});
    */
   

    //tree.balance();

    //	bst<int,int> tree_copy{std::move(tree)};

    //tree_copy.insert({4,8});

    //tree_copy.emplace(10,7);

    //std::cout << tree_copy << std::endl;

    //tree_copy = ;
	
    //tree[5] = 50;

    //tree.erase();
    //	std::cout << tree_copy << std::endl;

    // std::cout << tree << std::endl;


    //std::cout << tree << std::endl;

  } catch (const std::exception& e) {
    std::cout << "I'm in catch\n";
    std::cerr << e.what() << std::endl;
    return 1;

  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n" << std::endl;
    return 2;
  }

  return 0;
}
