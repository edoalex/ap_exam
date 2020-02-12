#ifndef __iterator_hpp
#define __iterator_hpp

#include<iostream>
#include<memory>
#include"bst.hpp"
#include"node.hpp"
#include"ap_error.h"

template<typename kt, typename vt, typename cmp>
template<typename node_type, typename pair_type>
class bst<kt, vt, cmp>::__iterator{//do we implement a class or a struct? He implemented a class also in the linked list
	
	node_type * _current;

	friend class bst<kt,vt,cmp>;
	
	explicit __iterator(node_type * x) : _current{x} {
		//std::cout << "iterator custom ctor" << std::endl;
	}

public:

	using reference = pair_type&;
	using pointer = pair_type*;
	using difference_type = std::ptrdiff_t;
	using iterator_category = std::forward_iterator_tag;

	//pair_type& operator*() const noexcept;
	reference operator*() const noexcept{
	  return _current->_element; // we return a reference to the element (pair: (k,v)) of the node to which the iterator is pointing to
	}


	//pair_type* operator->() const noexcept;
	pointer operator->() const noexcept{
		return &(*(*this)); // we return the pointer to the element (pair: (k,v)) of the node to which the iterator is pointing to
	}


  __iterator& operator++(){
    AP_ERROR( _current != nullptr ) << "It is not allowed to increment an iterator pointing to nullptr" << std::endl;
    //std::cout<< "pre incremenent" << std::endl;
    // if( non posso andare in basso dx )
    if(_current->_right == nullptr){
      // while( non posso andare alto dx )
      while(_current->_parent != nullptr && ((_current->_parent)->_left).get() != _current){
	// vai in alto sx
	_current = _current->_parent;
      }
      _current = _current->_parent;
      return *this;
    }
    else{
      _current = (_current->_right).get();
      // vai in basso sx finchè puoi
      while(_current->_left != nullptr){
	_current = (_current->_left).get();
      }
      return *this;
    }
  }

	__iterator operator++(int){
      AP_ERROR( _current != nullptr ) << "It is not allowed to increment an iterator pointing to nullptr" << std::endl;
	  //std::cout<< "post incremenent" << std::endl;
		__iterator tmp{_current};
		++(*this);
		return tmp;
	}

	friend bool operator==(const __iterator& a, const __iterator& b){
		return a._current == b._current;
	}

	friend bool operator!=(const __iterator& a, const __iterator& b){
		return !(a == b);
	}

};

#endif