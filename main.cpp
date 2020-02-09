#include"bst_prova.hpp"
#include<iostream>

int main(){
	bst<int,int> tree{};

	//	const std::pair<int,int> x = std::make_pair<int,int>(2,2);
	tree.insert({8,8});
	tree.insert({4,4});
	tree.insert({2,2});
	tree.insert({1,1});
	tree.insert({3,3});
	tree.insert({6,1});
	tree.insert({5,2});
	tree.insert({7,1});
	tree.insert({12,12});
	tree.insert({10,10});
	tree.insert({9,9});
	tree.insert({11,11});
	tree.insert({14,14});
	tree.insert({13,13});
	tree.insert({15,15});
	
	std::cout << tree << std::endl;

	tree.erase(8);

	std::cout << tree << std::endl;
	
	return 0;
}
