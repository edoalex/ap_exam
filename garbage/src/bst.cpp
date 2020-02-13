#include<iostream>
#include<memory>
#include<utility>
#include"bst.hpp"

template <typename kt, typename vt, typename cmp>
bool bst<kt, vt, cmp>::op_eq(const kt& x,const kt& y){//reference?
	return (op(x, y) == false && op(y, x) == false) ? true : false;
}

template <typename kt, typename vt, typename cmp>
bst<kt, vt, cmp>::bst(cmp op): _op{op} {std::cout << "bst custom ctor" << std::endl;}


template <typename kt, typename vt, typename cmp>
bst<kt, vt, cmp>::bst(const bst& B) {std::cout << "bst custom copy ctor" << std::endl;}

template <typename kt, typename vt, typename cmp>
bst<kt, vt, cmp>::bst(bst&& B) {std::cout << "bst move ctor" << std::endl;} 

template <typename kt, typename vt, typename cmp>
bst<kt, vt, cmp>& bst<kt, vt, cmp>::operator=(const bst& B) {} //copy assignment

template <typename kt, typename vt, typename cmp>
bst<kt, vt, cmp>& bst<kt, vt, cmp>::operator=(bst&& B) {} //move assignment

template <typename kt, typename vt, typename cmp>
std::pair<typename bst<kt, vt, cmp>::iterator, bool> bst<kt, vt, cmp>::insert(const pair_type& x){ //check if it can be optimized
	if (head == nullptr){
		head.reset(new node_type{x, nullptr}); // maybe nullprt = make_shared(nullptr)
		return std::make_pair(iterator{head.get()}, true);
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

template <typename kt, typename vt, typename cmp>
std::pair<typename bst<kt, vt, cmp>::iterator, bool> bst<kt, vt, cmp>::insert(pair_type&& x){ //check if it can be optimized
	if (head == nullptr){
		head.reset(new node_type{std::move(x), nullptr}); // maybe nullprt = make_shared(nullptr)
		return std::make_pair(iterator(head.get(), true));
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

template <typename kt, typename vt, typename cmp>
template<class... Types>
std::pair<typename bst<kt, vt, cmp>::iterator,bool> bst<kt, vt, cmp>::emplace(Types&&... args){}

template <typename kt, typename vt, typename cmp>
void bst<kt, vt, cmp>::clear(){}

template <typename kt, typename vt, typename cmp>
typename bst<kt, vt, cmp>::iterator bst<kt, vt, cmp>::begin(){
	node_type * it = head.get();
	while(it->_left != nullptr){
		it = it->_left;
	}
	return iterator{*it};
}

template <typename kt, typename vt, typename cmp>
typename bst<kt, vt, cmp>::const_iterator bst<kt, vt, cmp>::begin() const{
	node_type * it = head.get();
	while(it->_left != nullptr){
		it = it->_left;
	}
	return const_iterator{*it};
}

template <typename kt, typename vt, typename cmp>
typename bst<kt, vt, cmp>::const_iterator bst<kt, vt, cmp>::cbegin() const{
	node_type * it = head.get();
	while(it->_left != nullptr){
		it = it->_left;
	}
	return const_iterator{*it};
}

template <typename kt, typename vt, typename cmp>
typename bst<kt, vt, cmp>::iterator bst<kt, vt, cmp>::end(){
	node_type * it = head.get();
	while(it->_right != nullptr){
		it = it->_right;
	}
	return iterator{*(it->_right)};//returns one past the last element
} 

template <typename kt, typename vt, typename cmp>
typename bst<kt, vt, cmp>::const_iterator bst<kt, vt, cmp>::end() const{
	node_type * it = head.get();
	while(it->_right != nullptr){
		it = it->_right;
	}
	return const_iterator{*(it->_right)};
}  

template <typename kt, typename vt, typename cmp>
typename bst<kt, vt, cmp>::const_iterator bst<kt, vt, cmp>::cend() const{
	node_type * it = head.get();
	while(it->_right != nullptr){
		it = it->_right;
	}
	return const_iterator{*(it->_right)};
} 

template <typename kt, typename vt, typename cmp>
typename bst<kt, vt, cmp>::iterator bst<kt, vt, cmp>::find(const kt& x){}

template <typename kt, typename vt, typename cmp>
typename bst<kt, vt, cmp>::const_iterator bst<kt, vt, cmp>::find(const kt& x) const{}

template <typename kt, typename vt, typename cmp>
void bst<kt, vt, cmp>::balance(){}

template <typename kt, typename vt, typename cmp>
vt& bst<kt, vt, cmp>::operator[](const kt& x){
	auto tmp = find(x);
	if(tmp._current == nullptr){
	  //			vt no_value{};
		auto pair = insert(std::make_pair(x, vt{})); // maybe vt no_value{}
		std::cout << "pair inserted" << std::endl;
		return (*(pair.first)).second;
	}
	return (*tmp).second;
}

template <typename kt, typename vt, typename cmp>
vt& bst<kt, vt, cmp>::operator[](kt&& x){
	auto tmp = find(x);//does it work like this? should we use forward and make a unique function? or auto y = std::move(x); find(y) ?
	if(tmp._current == nullptr){
		vt no_value{};
		insert(std::make_pair(std::move(x), no_value));
		std::cout << "pair inserted" << std::endl;
		return no_value;
	}
	return (*tmp).second;
}

template <typename kt, typename vt, typename cmp>
std::ostream& operator<<(std::ostream& os, const bst<kt, vt, cmp>& x){
	auto it = x.cbegin();
	auto end = x.cend();
	while(it != end){
		os << (*it).first << " : " << (*it).second << std::endl; 
		++it;
	}
	return os;
}

template <typename kt, typename vt, typename cmp>
void bst<kt, vt, cmp>::erase(const kt& x){}


//node

template <typename kt, typename vt, typename cmp>
template <typename pair_type>
bst<kt, vt, cmp>::node<pair_type>::node(pair_type&& element, const node * parent) noexcept :
				_element{std::move(element)}, _parent{parent} {std::cout << "node move ctor" << std::endl;}

template <typename kt, typename vt, typename cmp>
template <typename pair_type>
bst<kt, vt, cmp>::node<pair_type>::node(const pair_type& element, const node * parent) : 
				_element{element}, _parent{parent} {std::cout << "node copy ctor" << std::endl;} //custom ctor

//iterator

template <typename kt, typename vt, typename cmp>
template<typename node_type, typename pair_type>
bst<kt, vt, cmp>::__iterator<node_type, pair_type>::__iterator(node_type * x) noexcept : _current{x} {}

template <typename kt, typename vt, typename cmp>
template<typename node_type, typename pair_type>
typename bst<kt, vt, cmp>::template __iterator<node_type, pair_type>::reference bst<kt, vt, cmp>::__iterator<node_type, pair_type>::operator*() const noexcept {
	return _current->_element; //here we return a reference to the pair(key, value)
}

template <typename kt, typename vt, typename cmp>
template<typename node_type, typename pair_type>
typename bst<kt, vt, cmp>::template __iterator<node_type, pair_type>::pointer bst<kt, vt, cmp>::__iterator<node_type, pair_type>::operator->() const noexcept{
	return &(*(*this)); // we return the pointer to the element (pair) of the node to which the iterator is pointing to
}

template <typename kt, typename vt, typename cmp>
template<typename node_type, typename pair_type>
typename bst<kt, vt, cmp>::template __iterator<node_type, pair_type>& bst<kt, vt, cmp>::__iterator<node_type, pair_type>::operator++() noexcept{ //do we need a second scope resolution?
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

template <typename kt, typename vt, typename cmp>
template<typename node_type, typename pair_type>
typename bst<kt, vt, cmp>::template __iterator<node_type, pair_type> bst<kt, vt, cmp>::__iterator<node_type, pair_type>::operator++(int) noexcept{
	iterator tmp{_current};
	++(*this);
	return tmp;
}
