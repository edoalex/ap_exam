#ifndef __bst_hpp
#define __bst_hpp

#include<memory>
#include<utility>

template <typename pair_type>
struct node{

	pair_type _element;

	std::shared_ptr<node> const _parent; //automatically destructs
	std::unique_ptr<node> _left;
	std::unique_ptr<node> _right;

	//we didn't implement a default constructor that initiates all the values of the node to 0
	//because we don't want to allow users to create multiple nodes with the same key
	//That's why we implemented a default constructor that deletes itself when called


	node() = delete;
	node(pair_type&& element, const node * parent) noexcept;

	node(const pair_type& element, const node * parent);


	~node();

};

template <typename kt, typename vt, typename cmp = std::less<kt>>
class bst{

	cmp _op;
	
	using node_type = node<std::pair<const kt, vt>>;
	
	std::unique_ptr<node_type> head;

	bool op_eq(const kt& x,const kt& y);

public:

	using iterator = iterator<node_type, typename node_type::pair_type>;
	using const_iterator = iterator<node_type, typename const node_type::pair_type>;

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

template<typename node_type, typename pair_type>
class iterator{//do we implement a class or a struct? He implemented a class also in the linked list
	
	std::shared_ptr<node_type> _current;

public:

	using reference = pair_type&;
	using pointer = pair_type*;
	using iterator_category = std::forward_iterator_tag;
	using difference_type = std::prtdiff_t;


	explicit iterator(node_type * x) noexcept;

	reference operator*() const noexcept;

	pointer operator->() const noexcept;

	iterator& operator++() noexcept;

	iterator operator++(int) noexcept;

	friend bool operator==(const iterator& a, const iterator& b);

	friend bool operator!=(const iterator& a, const iterator& b);



};


#endif
