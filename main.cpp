#include"bst.hpp"
#include<iostream>

int main(){
	bst<int,int> tree{};
	tree.insert({5,8});
	tree.insert({2,2});
	tree.insert({3,4});
	tree.insert({1,1});
	tree.insert({4,3});
	tree.insert({6,1});
	/*tree.insert({5,2});
	tree.insert({7,1});
	tree.insert({12,12});
	tree.insert({10,10});
	tree.insert({9,9});
	tree.insert({11,11});
	tree.insert({14,14});
	tree.insert({13,13});
	tree.insert({15,15});
	*/
	std::cout << tree << std::endl;

	tree.erase(3);

	std::cout << tree << std::endl;
	
	return 0;
}
