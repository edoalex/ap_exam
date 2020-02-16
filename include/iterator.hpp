/**
 * @file iterator.hpp
 * @author Edoardo Alessandroni 
 * @author Alberto Luvisutto
 * @author Andrea Mecchina 
 * @date 13 February 2020
 * @brief Header containing iterator class implementation.
 */

#ifndef __iterator_hpp
#define __iterator_hpp

#include<iostream> // << operator
#include<memory> // unique pointers
#include"ap_error.h" // exceptions
#include"bst.hpp"
#include"node.hpp"
#include"bst_functions.hpp"

/**
 * @brief Templated implementation of an iterator class.
 * @tparam node_type Type of the node pointed by the iterator.
 * @tparam pair_type Type of the const or non const pair.
 */

template<typename kt, typename vt, typename cmp>
template<typename node_type, typename pair_type>
class bst<kt, vt, cmp>::__iterator{
	
	/** @brief Pointer to a node. */
	
	node_type * _current;

	/** Used to give access to the private members of the class. */
	
	friend class bst<kt,vt,cmp>;
	
	/**
 	 * @brief Iterator custom constructor.
	 * @param x Pointer to a node.
	 */
	
	explicit __iterator(node_type * x) : _current{x} {
		//std::cout << "iterator custom ctor" << std::endl;
	}

public:

	/** Alias to make names shorter and intuitive. */
	
	using reference = pair_type&;
	
	/** Alias to make names shorter and intuitive. */
	
	using pointer = pair_type*;
	
	/** Alias to make names shorter and intuitive. */
	
	using difference_type = std::ptrdiff_t;
	
	/** Alias to make names shorter and intuitive. */
	
	using iterator_category = std::forward_iterator_tag;

	/**
	 * @brief Operator * overloading to access the data of a node.
	 * @return reference A reference to the data of node pointed by the iterator.
	 */

	reference operator*() const noexcept{
	  return _current->_element; 
	}
	
	/**
	 * @brief Operator -> overloading to access the data of a node.
	 * @return pointer A pointer to the data of node pointed by the iterator.
	 */

	pointer operator->() const noexcept{
		return &(*(*this));
	}

	/**
	 * @brief Operator ++it overloading to move the iterator to the next node.
	 * @return __iterator& A reference to the incremented iterator.
	 */

  	__iterator& operator++(){
   		AP_ERROR( _current != nullptr ) << "It is not allowed to increment an iterator pointing to nullptr" << std::endl;
    	//std::cout<< "pre incremenent" << std::endl;
    	if(_current->_right == nullptr){
     	 	// while( can't go up right)
     	 	while(_current->_parent != nullptr && ((_current->_parent)->_left).get() != _current){
				//go up left
				_current = _current->_parent;
    	  	}
    		_current = _current->_parent;
    		return *this;
   	 	} else {
     	 
     		_current = (_current->_right).get();
      		//go down left while you can
      		while(_current->_left != nullptr){
				_current = (_current->_left).get();
      		}
      		
      		return *this;
    	}
  	}

	/**
	 * @brief Operator it++ overloading to move the iterator to the next node.
	 * @return __iterator Value of the iterator before moving to the next node.
	 */

	__iterator operator++(int){
      AP_ERROR( _current != nullptr ) << "It is not allowed to increment an iterator pointing to nullptr" << std::endl;
	  //std::cout<< "post incremenent" << std::endl;
		__iterator tmp{_current};
		++(*this);
		return tmp;
	}
	
	/**
	 * @brief Operator == overloading to check if the iterators are equal.
	 * @param a First iterator to be compared.
	 * @param b Second iterator to be compared.
	 * @return bool Returns true if the iterators points to the same node, else false.
	 */

	friend bool operator==(const __iterator& a, const __iterator& b){
		return a._current == b._current;
	}
	
	/**
	 * @brief Operator != overloading to check if the iterators are unequal.
	 * @param a First iterator to be compared.
	 * @param b Second iterator to be compared.
	 * @return bool Returns true if the iterators don't point to the same node, else false.
	 */
	 
	friend bool operator!=(const __iterator& a, const __iterator& b){
		return !(a == b);
	}

};

#endif