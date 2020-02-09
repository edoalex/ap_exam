#include"bst_prova.hpp"
#include<iostream>

int main(){
	bst<int,int> tree{};

	const std::pair<int,int> x = std::make_pair<int,int>(9,4);

	tree.insert({8,3});
	tree.insert(x);
	tree.insert({12,3});

	//tree.find(8);
	//tree.find(99);

	//int key = 8;
	//std::cout << "key = " << key << " holds value = " << tree[key] << std::endl;
	
	std::cout << tree << std::endl;

	tree.clear();

	std::cout << "HELLO TREE" << std::endl;
	
	std::cout << tree << std::endl;
	
	return 0;
}
