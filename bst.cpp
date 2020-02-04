#include<iostream>
#include<memory>
#include<utility>

template <typename T>
struct node{

	T _element;

	std::shared_ptr<node> _parent; //automatically destructs
	std::unique_ptr<node> _left;
	std::unique_ptr<node> _right;

	node(const T& element, const node * parent) : 
		_element{element}, _parent{parent} {std::cout << "node custom ctor" << std::endl;} //custom ctor
		//_left and _right default set to nullptr since the constructor is called only by insert
		//which always adds leaves to the tree which have no children

	~node() {std::cout << "node custom dtor" << std::endl;}

};

template <typename kt, typename vt, typename cmp = std::less<kt>>
class bst{
	cmp _op;

	using node_type = node<std::pair<const kt, vt>>;

	std::unique_ptr<node_type> head;  //maybe node templated ; is unique needed? 

public:

	//add iterator using after iterator class

	bst() noexcept = default; //default ctor
	bst(cmp op): _op{op} {std::cout << "bst custom ctor" << std::endl;} //custom ctor //test precondition with dynamic_cast
	bst(const bst& B) {std::cout << "bst custom copy ctor" << std::endl;} //copy ctor
	bst(bst&& B) {std::cout << "bst move ctor" << std::endl;} //move ctor non serve no

	bst& operator=(const bst& B) {} //copy assignment
	bst& operator=(bst&& B) {} //move assignment se non serve no

	~bst() {std::cout << "bst custom dtor" << std::endl;}

	//std::pair<iterator, bool> insert(const pair_type& x);
	//std::pair<iterator, bool> insert(pair_type&& x);

	//template< class... Types >
	//std::pair<iterator,bool> emplace(Types&&... args);

	void clear();
/*
	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;

	iterator end();
	const_iterator end() const;
	const_iterator cend() const;

	iterator find(const kt& x);
	const_iterator find(const kt& x) const;
*/
	void balance();

	vt& operator[](const kt& x);//key_type hanged to kt
	vt& operator[](kt&& x);

	template <typename KT, typename VT, typename CMP>
	friend std::ostream& operator<<(std::ostream& os, const bst<KT, VT, CMP>& x);

	void erase(const kt& x);

};

int main() {

	return 0;
}