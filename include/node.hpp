/**
 * @file node.hpp
 * @author Edoardo Alessandroni 
 * @author Alberto Luvisutto
 * @author Andrea Mecchina 
 * @date 13 February 2020
 * @brief Header containing node struct implementation.
 */

#ifndef __node_hpp
#define __node_hpp

#include<iostream> // << operator
#include<memory> // unique pointers
#include<utility> // pair
#include"ap_error.h" // exceptions
#include"bst.hpp"
#include"iterator.hpp"
#include"bst_functions.hpp"

/**
 * @brief Templated implementation of a node struct.
 * @tparam pair_type Type of the pair key and value.
 */

template <typename kt, typename vt, typename cmp>
template <typename pair_type>
struct bst<kt, vt, cmp>::node{

	/** @brief Element of the node. */

	pair_type _element;

	/** @brief Parent of the node. */

	node * _parent{};

	/** @brief Left child of the node. */

	std::unique_ptr<node> _left;
	
	/** @brief Right child of the node. */	
	
	std::unique_ptr<node> _right;

/**
 * @brief Node default constructor.
 * 
 * An exception is thrown since it is not allowed
 * to create a node without providing a key. 
 */

  node() {
    AP_ERROR(false) << "It is not allowed to create a node with no key provided" << std::endl;
  }
  
/**
 * @brief Custom node constructor.
 * @param twin Pointer to the node to be copied.
 * @param to_stick Pointer to the parent of the node to be constructed.
 * 
 * This constructor is only called iteratively by the
 * tree custom copy constructor and copy assignment. 
 */

  node(node * twin, node * to_stick) : _element{twin->_element}, _parent{to_stick} {

    //std::cout << "explicit iterative ctor" << std::endl;
    if((twin->_left).get() != nullptr){
      //std::cout << "constructing the left child of node with key = " << _element.first << std::endl;
      _left = std::make_unique<node>((twin->_left).get(), this);
    }

    if((twin->_right).get() != nullptr){
      //std::cout << "constructing the right child of node with key = " << _element.first << std::endl;
      _right = std::make_unique<node>((twin->_right).get(), this);		
    }	
  }

 /**
  * @brief Node move constructor.
  * @param element The data to be moved into the node.
  * @param parent Pointer to the parent of the node to be constructed.
  *
  * The two unique pointers are by default initialised as nullpointers.
  */

  node(pair_type&& element, node * parent) noexcept : _element{std::move(element)}, _parent{parent} {
    // std::cout << "key from old ctor = " << element.first << " value from old ctor = " << element.second << std::endl;
  }
	
 /**
  * @brief Node copy constructor.
  * @param element The data to be copied into the node.
  * @param parent Pointer to the parent of the node to be constructed.
  *
  * The two unique pointers are by default initialised as nullpointers.
  */	
	
  node(const pair_type& element, node * parent) : _element{element}, _parent{parent} {}

 /**
  * @brief Custom node constructor.
  * @param k The key to be moved into the pair.
  * @param v The value to be moved into the pair.
  *
  * This constructor is only called by the emplace function.
  */	
  
  node(kt&& k, vt&& v) noexcept : _element{std::make_pair<kt,vt>(std::move(k), std::move(v))} {
    //std::cout << "key from new ctor = " << k << " value from new ctor = " << v << std::endl;
  } 
};

#endif
