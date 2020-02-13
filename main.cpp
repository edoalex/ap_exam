#include"bst.hpp"
#include<iostream>
#include<chrono>

int main(){

  try {
   
    bst<int,int> tree{};
    //tree.insert({1,2});

    //bst<int,int> tree_2{};
    //std::cout << tree << std::endl;
    //tree_2 = tree;
    //tree_2.insert({1,2});
    //tree.emplace(std::make_pair<int,int>(9,5),nullptr);
    //tree.insert({0,2});
    //std::cout << tree << std::endl;
    // tree.emplace(1,2);
    //throw std::runtime_error("Are there leaks?");
	

      tree.insert({0,3});
      tree.insert({1,10});
      tree.insert({2,12});
      tree.insert({3,11});
      tree.insert({4,15});
      tree.insert({5,9});
      tree.insert({6,1});
      tree.insert({7,2});
      tree.insert({8,1});
      tree.insert({9,14});
      tree.insert({10,13});

      std::cout << tree << std::endl;
      
      auto a = 3;
      tree[22] = 22;
      tree[a] = a;

      std::cout << tree << std::endl;

      
      
      // for(auto x : tree){ std::cout << x.first << std::endl; }
    

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
    std::cerr << e.what() << std::endl;
    return 1;

  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n" << std::endl;
    return 2;
  }

  return 0;
}
