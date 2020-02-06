#include<iostream>
#include<memory>
#include<utility>
#include<bst.hpp>

template <typename pair_type>
struct node{//it's a struct because we are going to need to access all the elements of the struct node

	pair_type _element;

	std::shared_ptr<node> const _parent; //automatically destructs
	std::unique_ptr<node> _left;
	std::unique_ptr<node> _right;

	//we didn't implement a default constructor that initiates all the values of the node to 0
	//because we don't want to allow users to create multiple nodes with the same key
	//That's why we implemented a default constructor that deletes itself when called

	node(pair_type&& element, const node * parent) noexcept :
		_element{std::move(element)}, _parent{parent} {std::cout << "node move ctor" << std::endl;}

	node(const pair_type& element, const node * parent) : 
		_element{element}, _parent{parent} {std::cout << "node copy ctor" << std::endl;} //custom ctor
		//_left and _right default set to nullptr since the constructor is called only by insert
		//which always adds leaves to the tree which have no children

	~node() {std::cout << "node dtor" << std::endl;}

	//the assignments (move and copy) are not implemented because the only cases in which we are going 
	//to need to modify an already existing node can be done by only changing some values
	//of the node itself; in any case, we don't have the subsituting node already available

};

template <typename kt, typename vt, typename cmp = std::less<kt>>
class bst{
	cmp _op;

	using node_type = node<std::pair<const kt, vt>>;

	std::unique_ptr<node_type> head;  //maybe node templated ; is unique needed? 

	bool op_eq(const kt& x,const kt& y){//reference?
		return (op(x, y) == false && op(y, x) == false) ? true : false;
	}

public:

	using iterator = iterator<node_type, typename node_type::pair_type>;
	using const_iterator = iterator<node_type, typename const node_type::pair_type>;


	bst(cmp op): _op{op} {std::cout << "bst custom ctor" << std::endl;} //custom ctor //test precondition with dynamic_cast
	bst(const bst& B) {std::cout << "bst custom copy ctor" << std::endl;} //copy ctor
	bst(bst&& B) {std::cout << "bst move ctor" << std::endl;} 

	bst& operator=(const bst& B) {} //copy assignment
	bst& operator=(bst&& B) {} //move assignment se non serve no

	~bst() {std::cout << "bst dtor" << std::endl;}

	std::pair<iterator, bool> insert(const pair_type& x){ //check if it can be optimized
	  if (head == nullptr){
	    head.reset(new node{x, nullptr}); // maybe nullprt = make_shared(nullptr)
	    return std::make_pair(iterator(head.get(), true));
	  }
		node_type * ptr = head.get();

		while(op_eq(x.first, (ptr->_element).first) == false){

			if(_op(x.first, (ptr->_element).first) == true){

				if(ptr->_left == nullptr){

					(ptr->_left).reset(new node{x, std::make_shared<node_type>(ptr)});
					return std::make_pair(iterator{(ptr->_left).get()}, true);

				}

				ptr = ptr->_left;
			}
			else{

				if(ptr->_right == nullptr){
					
					(ptr->_right).reset(new node{x, std::make_shared<node_type>(ptr)});
					return std::make_pair(iterator{(ptr->_right).get()}, true);

				}

				ptr = ptr->_right;
			}
		}

		return std::make_pair(iterator{nullptr}, false);
	}

	std::pair<iterator, bool> insert(pair_type&& x){ //check if it can be optimized
	  if (head == nullptr){
	    head.reset(new node{std::move(x), nullptr}); // maybe nullprt = make_shared(nullptr)
	    return std::make_pair(iterator(head.get(), true));
	  }
	  node_type * ptr = head.get();
		
		while(op_eq(x.first, (ptr->_element).first) == false){

			if(_op(x.first, (ptr->_element).first) == true){

				if(ptr->_left == nullptr){

					(ptr->_left).reset(new node{std::move(x), std::make_shared<node_type>(ptr)});
					return std::make_pair(iterator{(ptr->_left).get()}, true);

				}

				ptr = ptr->_left;
			}
			else{

				if(ptr->_right == nullptr){
					
					(ptr->_right).reset(new node{std::move(x), std::make_shared<node_type>(ptr)});
					return std::make_pair(iterator{(ptr->_right).get()}, true);

				}

				ptr = ptr->_right;
			}
		}

		return std::make_pair(iterator{nullptr}, false);
	}

	template<class... Types>
	std::pair<iterator,bool> emplace(Types&&... args);

	void clear();

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

	//we need a find that receives an rvalue; do we template it and use std::forward or do we implement two functions?
	iterator find(const kt& x);
	const_iterator find(const kt& x) const;

	void balance();

	vt& operator[](const kt& x){
		auto tmp = find(x);
		if(tmp._current == nullptr){
			vt no_value{};
			insert(std::make_pair(x, no_value));
			std::cout << "pair inserted" << std::endl;
			return no_value;
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
	friend std::ostream& operator<<(std::ostream& os, const bst& x){
	  auto it = cbegin();
	  auto end = cend();
	  while(it != end){
	    os << (*it).first << " : " << (*it).second << std::endl; 
	    ++it;
	  }
	  return os;
	}

	void erase(const kt& x);

};

//in linked list class iterator is templated, and declared inside class list;
//should we do the same? In case, add a template with 3 values and put bst<KT,VT,CMP>::iterator

template<typename node_type, typename pair_type>
class iterator{
	
	std::shared_ptr<node_type> _current;

public:

	using reference = pair_type&;
	using pointer = pair_type*;
	using iterator_category = std::forward_iterator_tag;
	using difference_type = std::prtdiff_t;

	explicit iterator(std::shared_ptr<node_type> node) noexcept : _current{node} {}

	reference operator*() const noexcept {
		return _current->_element; //here we return a reference to the pair(key, value)
	}

	pointer operator->() const noexcept{
		return &(*(*this)); // we return the pointer to the element (pair) of the node to which the iterator is pointing to
	}
  
	iterator& operator++() noexcept{
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

	iterator operator++(int) noexcept{
		iterator tmp{_current};
		++(*this);
		return tmp;
	}

	friend bool operator==(const iterator& a, const iterator& b) {
		return a._current == b._current;
	}
	friend bool operator!=(const iterator& a, const iterator& b) {
		return !(a == b);
	}

};

int main() {

	return 0;
}
