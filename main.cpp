#include"bst.hpp"
#include<iostream>

int main(){
	bst<int,int> tree{};
	tree.insert({1,2});
	tree.insert({2,1});
	tree.insert({3,1});
	tree.insert({4,1});
	tree.insert({5,3});
	tree.insert({6,3});
	tree.insert({7,8});
	tree.insert({8,3});
	/*
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

	std::cout << tree << std::endl;

	//tree.balance();

	bst<int,int> tree_copy{tree};
	
	tree[5] = 50;
	//tree.erase();

	std::cout << tree << std::endl;

	std::cout << tree_copy << std::endl;

	//std::cout << tree << std::endl;

	return 0;
}
