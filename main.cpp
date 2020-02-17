#include"bst.hpp"
#include<iostream>
#include<chrono>

int main(){

  try {
   
    bst<int,int> tree{};
    std::pair<int,int> node = {1,1};
    tree.insert( node );

    bst<int,int> tree_m = std::move(tree);
    bst<int,int> tree_c = tree_m;

    tree_c.insert({2,2});
    tree_m.insert({3,3});
    tree.insert({4,4});
    
    std::cout << "tree:\n" << tree << std::endl;
    std::cout << "tree_m:\n"<< tree_m << std::endl;
    std::cout << "tree_c:\n"<< tree_c << std::endl;

    tree = tree_c;

    tree.emplace(5,5);
    tree.emplace(6,6);

    tree[5] = 555;
    auto key = 6;
    tree[key] = 66;
    tree.erase(2);

    tree_m.clear();
    tree_m = std::move(tree_c);
    std::cout << "\n\ntree:\n" << tree << std::endl;
    std::cout << "tree_m:\n"<< tree_m << std::endl;
    std::cout << "tree_c:\n"<< tree_c << std::endl;

    for(auto i=0; i<10; ++i){
      tree.insert({i,i});
    }
    
    tree[10] = 10;
    tree.balance();

    auto it = tree.find(4);
    auto sentinel = tree.end();
    
    while( it != sentinel ){
      std::cout << "key: " << it->first
		<< "\tvalue: " << (*it).second
		<< std::endl;
		++it;
		}
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;

  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n" << std::endl;
    return 2;
  }

  return 0;
}
