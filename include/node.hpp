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

	pair_type _element;

	node * _parent{}; //const removed when writing erase
	std::unique_ptr<node> _left;
	std::unique_ptr<node> _right;

	//we didn't implement a default constructor that initiates all the values of the node to 0
	//because we don't want to allow users to create multiple nodes with the same key
	//That's why we implemented a default constructor that deletes itself when called

  node() {
    AP_ERROR(false) << "It is not allowed to create a node with no key provided" << std::endl;
  }

  explicit node(node * twin, node * to_stick) : _element{twin->_element}, _parent{to_stick} {

    std::cout << "explicit iterative ctor" << std::endl;
    if((twin->_left).get() != nullptr){
      std::cout << "constructing the left child of node with key = " << _element.first << std::endl;
      _left = std::make_unique<node>((twin->_left).get(), this);
    }

    if((twin->_right).get() != nullptr){
      std::cout << "constructing the right child of node with key = " << _element.first << std::endl;
      _right = std::make_unique<node>((twin->_right).get(), this);		
    }	
  }

  node(pair_type&& element, node * parent) noexcept : _element{std::move(element)}, _parent{parent} {
    // std::cout << "key from old ctor = " << element.first << " value from old ctor = " << element.second << std::endl;
  } //removed a const before node || do I need to write const node * parent?
	
  node(const pair_type& element, node * parent) : _element{element}, _parent{parent} {} //custom ctor

  node(kt&& k, vt&& v) noexcept : _element{std::make_pair<kt,vt>(std::move(k), std::move(v))}	{
    std::cout << "key from new ctor = " << k << " value from new ctor = " << v << std::endl;
    //node(std::make_pair<kt,vt>(std::move(k),std::move(v)), nullptr);
  } 

  ~node() {std::cout << "node dtor with key " << (this->_element).first << std::endl;} //do we need to delete the raw pointer??
};

#endif
