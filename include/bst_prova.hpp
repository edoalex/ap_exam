#ifndef __bst_hpp
#define __bst_hpp

#include<memory>
#include<utility>
#include<iostream>


template <typename kt, typename vt, typename cmp = std::less<kt>>
class bst{
    template<typename node_type, typename pair_type>
    class __iterator;

    template <typename pair_type>
    struct node;
  
	cmp _op;
	
	using node_type = node<std::pair<const kt, vt>>;
	
	std::unique_ptr<node_type> head;

	bool op_eq(const kt& x,const kt& y){//reference?
		return (op(x, y) == false && op(y, x) == false) ? true : false;
	}

public:
	using pair_type = std::pair<const kt, vt>;
    //using pair_type = typename node_type::pair_type;
	using iterator = __iterator<node_type, pair_type>;	
	using const_iterator = __iterator<node_type, const pair_type>;

	//constructors and destructors:
	//note that these constructors can go only in the header if they are default constructors!!
	bst() noexcept = default; //default ctor
	bst(cmp op): _op{op} {std::cout << "bst custom ctor" << std::endl;}
	bst(const bst& B){std::cout << "bst custom copy ctor" << std::endl;}
	bst(bst&& B){std::cout << "bst move ctor" << std::endl;} 

	//operator overloading:
	//do we need to put in the headers also the operator overloading? Probably yes, they are still functions
	bst& operator=(const bst& B){} //copy assignment
	bst& operator=(bst&& B){} //move assignment

	~bst() = default;


	//functions to implement:

  
	std::pair<iterator, bool> insert(const pair_type& x){ //check if it can be optimized
	if (head == nullptr){
		head.reset(new node_type{x, nullptr}); // maybe nullprt = make_shared(nullptr)
		return std::make_pair(iterator(head.get(), true));
	}
	node_type * ptr = head.get();

	while(op_eq(x.first, (ptr->_element).first) == false){

		if(_op(x.first, (ptr->_element).first) == true){

			if(ptr->_left == nullptr){
				(ptr->_left).reset(new node_type{x, std::make_shared<node_type>(ptr)});
				return std::make_pair(iterator{(ptr->_left).get()}, true);
			}
			ptr = ptr->_left;
		}
		else{
			if(ptr->_right == nullptr){
				(ptr->_right).reset(new node_type{x, std::make_shared<node_type>(ptr)});
				return std::make_pair(iterator{(ptr->_right).get()}, true);
			}
			ptr = ptr->_right;
		}
	}
	return std::make_pair(iterator{nullptr}, false);
}
	std::pair<iterator, bool> insert(pair_type&& x){ //check if it can be optimized
	if (head == nullptr){
		head.reset(new node_type{std::move(x), nullptr}); // maybe nullprt = make_shared(nullptr)
		return std::make_pair(iterator{head.get()}, true);
	}
	node_type * ptr = head.get();

	while(op_eq(x.first, (ptr->_element).first) == false){

		if(_op(x.first, (ptr->_element).first) == true){

			if(ptr->_left == nullptr){
				
				(ptr->_left).reset(new node_type{std::move(x), std::make_shared<node_type>(ptr)});

				return std::make_pair(iterator{(ptr->_left).get()}, true);
			}
			ptr = ptr->_left;
		}else{

			if(ptr->_right == nullptr){

				(ptr->_right).reset(new node_type{std::move(x), std::make_shared<node_type>(ptr)});
				return std::make_pair(iterator{(ptr->_right).get()}, true);
			}
			ptr = ptr->_right;
		}
	}

	return std::make_pair(iterator{nullptr}, false);
}

	template<class... Types>
	std::pair<iterator,bool> emplace(Types&&... args){}

	void clear(){}

	iterator begin(){
	node_type * it = head.get();
	while(it->_left != nullptr){
		it = it->_left;
	}
	return iterator{*it};
}
	const_iterator begin() const{
	node_type * it = head.get();
	while(it->_left != nullptr){
		it = it->_left;
	}
	return const_iterator{*it};
}
	const_iterator cbegin() const{
	node_type * it = head.get();
	while(it->_left != nullptr){
		it = it->_left;
	}
	return const_iterator{*it};
}

	iterator end(){
	node_type * it = head.get();
	while(it->_right != nullptr){
		it = it->_right;
	}
	return iterator{*(it->_right)};//returns one past the last element
} 

	const_iterator end() const{
	node_type * it = head.get();
	while(it->_right != nullptr){
		it = it->_right;
	}
	return const_iterator{*(it->_right)};
}  
	const_iterator cend() const{
	node_type * it = head.get();
	while(it->_right != nullptr){
		it = it->_right;
	}
	return const_iterator{*(it->_right)};
} 

	iterator find(const kt& x){}
	const_iterator find(const kt& x) const{}

	void balance(){}

	vt& operator[](const kt& x){
	auto tmp = find(x);
	if(tmp._current == nullptr){
	  //			vt no_value{};
		auto pair = insert(std::make_pair(x, vt{})); // maybe vt no_value{}
		std::cout << "pair inserted" << std::endl;
		return (*(pair.first)).second;
	}
	return (*tmp).second;
}
	vt& operator[](kt&& x){
	auto tmp = find(x);//does it work like this? should we use forward and make a unique function? or auto y = std::move(x); find(y) ?
	if(tmp._current == nullptr){
		vt no_value{};
		insert(std::make_pair(std::move(x), no_value));
		std::cout << "pair inserted" << std::endl;
		return no_value;
	}
	return (*tmp).second;
}

	template <typename KT, typename VT, typename CMP>
	friend std::ostream& operator<<(std::ostream& os, const bst<KT, VT, CMP>& x){
	auto it = x.cbegin();
	auto end = x.cend();
	while(it != end){
		os << (*it).first << " : " << (*it).second << std::endl; 
		++it;
	}
	return os;
}


	void erase(const kt& x){}
};


template <typename kt, typename vt, typename cmp>
template <typename pair_type>
struct bst<kt, vt, cmp>::node{

	pair_type _element;

	std::shared_ptr<node> const _parent; //automatically destructs
	std::unique_ptr<node> _left;
	std::unique_ptr<node> _right;

	//we didn't implement a default constructor that initiates all the values of the node to 0
	//because we don't want to allow users to create multiple nodes with the same key
	//That's why we implemented a default constructor that deletes itself when called


	node() = delete;
	node(pair_type&& element, const node * parent) noexcept : _element{std::move(element)}, _parent{parent} {std::cout << "node move ctor" << std::endl;}

	node(const pair_type& element, const node * parent) : _element{element}, _parent{parent} {std::cout << "node copy ctor" << std::endl;} //custom ctor


	~node() = default;

};

template<typename kt, typename vt, typename cmp>
template<typename node_type, typename pair_type>
class bst<kt, vt, cmp>::__iterator{//do we implement a class or a struct? He implemented a class also in the linked list
	
	std::shared_ptr<node_type> _current;

public:

	using reference = pair_type&;
	using pointer = pair_type*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;



	explicit __iterator(node_type* x) noexcept: _current{x} {}

	//pair_type& operator*() const noexcept;
	reference operator*() const noexcept{
	return _current->_element; //here we return a reference to the pair(key, value)
}


	//pair_type* operator->() const noexcept;
	pointer operator->() const noexcept{
	return &(*(*this)); // we return the pointer to the element (pair) of the node to which the iterator is pointing to
}


	__iterator& operator++() noexcept{ //do we need a second scope resolution?
	// if( non posso andare in basso dx )
	if(_current->_right == nullptr){
		// while( non posso andare alto dx )
		while(_current->_parent != nullptr && (_current->_parent)->_left != _current){
			// vai in alto sx
			_current = _current->_parent;
		}
		_current = _current->_parent;
		return *this;
	}
	else{
		_current = _current->_right;
		// vai in basso sx finchè puoi
		while(_current->_left != nullptr){
			_current = _current->_left;
		}
		return *this;
	}
}


	__iterator operator++(int) noexcept{
	iterator tmp{_current};
	++(*this);
	return tmp;
}

  template<typename Node_type, typename Pair_type>  
  friend bool operator==(const __iterator<Node_type, Pair_type>&, const __iterator<Node_type, Pair_type>&);   // do we need `friend`?

  template<typename Node_type, typename Pair_type>  
  friend bool operator!=(const __iterator<Node_type, Pair_type>&, const __iterator<Node_type, Pair_type>&);

};

#endif
