#include"bst_prova.hpp"
#include<iostream>

int main(){
	bst<int,int> tree{};
	//tree.insert({8,150});
	const std::pair<int,int> x = std::make_pair<int,int>(9,4);
	tree.insert({8,3});
	tree.insert(x);
	tree.insert({12,3});
	tree.insert({2,2});
	tree.insert({6,3});
	tree.insert({10,3});
	tree.insert({14,3});
	tree.insert({1,3});
	tree.insert({3,3});
	tree.insert({5,3});
	tree.insert({7,3});
	tree.insert({9,3});
	tree.insert({11,3});
	tree.insert({13,3});
	tree.insert({15,3});
	
	std::cout << tree << std::endl;
	return 0;
}
