#include<iostream>
#include<memory>
#include<utility>

template <typename T>
struct node{//it's a struct because we are going to need to access all the elements of the struct node

	T _element;

	std::shared_ptr<node> _parent; //automatically destructs
	std::unique_ptr<node> _left;
	std::unique_ptr<node> _right;

	//should we implement explicitely a default ctor for the node?

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

	//add using iterator after implementing iterator class
	using iterator = iterator<node_type, typename node_type::value_type>;
	using const_iterator = iterator<node_type, typename const node_type::value_type>;


	bst(cmp op): _op{op} {std::cout << "bst custom ctor" << std::endl;} //custom ctor //test precondition with dynamic_cast
	bst(const bst& B) {std::cout << "bst custom copy ctor" << std::endl;} //copy ctor
	bst(bst&& B) {std::cout << "bst move ctor" << std::endl;} //move ctor non serve no

	bst& operator=(const bst& B) {} //copy assignment
	bst& operator=(bst&& B) {} //move assignment se non serve no

	~bst() {std::cout << "bst custom dtor" << std::endl;}

	std::pair<iterator, bool> insert(const pair_type& x);
	std::pair<iterator, bool> insert(pair_type&& x);

	template<class... Types>
	std::pair<iterator,bool> emplace(Types&&... args);

	void clear();

	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;

	iterator end();
	const_iterator end() const;
	const_iterator cend() const;

	iterator find(const kt& x);
	const_iterator find(const kt& x) const;

	void balance();

	vt& operator[](const kt& x);//key_type hanged to kt
	vt& operator[](kt&& x);

	template <typename KT, typename VT, typename CMP>
	friend std::ostream& operator<<(std::ostream& os, const bst<KT, VT, CMP>& x);

	void erase(const kt& x);

};

//in linked list class iterator is templated, and declared inside class list;
//should we do the same? In case, add a template with 3 values and put bst<KT,VT,CMP>::iterator

template<typename node_type, typename T>
class iterator{//do we implement a class or a struct? He implemented a class also in the linked list
	
	node_type * current;

public:
	
	using value_type = T;
	using reference = value_type&;
	using pointer = value_type*;
	using iterator_category = std::forward_iterator_tag;
	using difference_type = std::prtdiff_t;

	explicit iterator(node_type * x) noexcept : current{x} {}

	reference operator*() const {
		return current->value_type;//WRONG! //do we want the value or the pair key-value?
	}

	friend bool operator==(const iterator& a, const iterator& b) {
		return a.current == b.current;
	}
	friend bool operator!=(const iterator& a, const iterator& b) {
		return !(a == b);
	}

};

int main() {

	return 0;
}