#ifndef __bst_hpp
#define __bst_hpp

#include<memory>
#include<utility>

template <typename T>
struct node{

	T _element;

	std::shared_ptr<node> _parent; //automatically destructs
	std::unique_ptr<node> _left;
	std::unique_ptr<node> _right;

	node(const T& element, const node * parent);

	~node();

};

template <typename kt, typename vt, typename cmp = std::less<kt>>
class bst{

	cmp _op;
	using node_type = node<std::pair<const kt, vt>>;
	std::unique_ptr<node_type> head;

public:

	using iterator = iterator<node_type, typename node_type::value_type>;
	using const_iterator = iterator<node_type, typename const node_type::value_type>;

	//constructors and destructors:
	//note that these constructors can go only in the header if they are default constructors!!
	bst() noexcept = default; //default ctor
	bst(cmp op);
	bst(const bst& B);
	bst(bst&& B);

	//operator overloading:
	//do we need to put in the headers also the operator overloading? Probably yes, they are still functions
	bst& operator=(const bst& B);
	bst& operator=(bst&& B);

	~bst();


	//functions to implement:

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

	vt& operator[](const kt& x);
	vt& operator[](kt&& x);

	template <typename KT, typename VT, typename CMP>
	friend std::ostream& operator<<(std::ostream& os, const bst<KT, VT, CMP>& x);

	void erase(const kt& x);

};

template<typename node_type, typename T>
class iterator{//do we implement a class or a struct? He implemented a class also in the linked list
	
	node_type * current;

public:
	
	using value_type = T;
	using reference = value_type&;
	using pointer = value_type*;
	using iterator_category = std::forward_iterator_tag;
	using difference_type = std::prtdiff_t;

	explicit iterator(node_type * x) noexcept;

	friend bool operator==(const iterator& a, const iterator& b);

	friend bool operator!=(const iterator& a, const iterator& b);



};


#endif
