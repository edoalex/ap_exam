/**
 * @file bst.hpp
 * @author Edoardo Alessandroni 
 * @author Alberto Luvisutto
 * @author Andrea Mecchina 
 * @date 13 February 2020
 * @brief Header containing bst class implementation.
 */
 
#ifndef __bst_hpp
#define __bst_hpp

#include<iostream> // << operator
#include<memory> // unique pointers
#include<utility> // pair
#include<vector> // vector class

/**
 * @brief Templated implementation of a binary search tree class.
 * @tparam kt Type of node keys.
 * @tparam vt Type of node values.
 * @tparam cmp Type of the custom comparison operator between nodes. Default std::less<kt>.
 */

template <typename kt, typename vt, typename cmp = std::less<kt>>
class bst{
	
	/**
	 * @brief Templated node struct with two children nodes and one parent node.
	 */

	template <typename pair_type>
	struct node;
	
	/**
	 * @brief Templated iterator class with a pointer to a node.
	 */
	
	template<typename node_type, typename pair_type>
	class __iterator;
	
	/**
	 * @brief Comparison operator for the binary search tree.
	 */
	
	cmp _op;
	
	using node_type = node<std::pair<const kt, vt>>;
	
	/** Root node of the binary search tree. */
	
	std::unique_ptr<node_type> head;

	bool op_eq(const kt& x,const kt& y) const noexcept {
		return (_op(x, y) == false && _op(y, x) == false) ? true : false;
	}

	void order(std::vector<std::pair<kt,vt>>& v) noexcept ;

public:

	using pair_type = std::pair<const kt, vt>;
	using iterator = __iterator<node_type, pair_type>;	
	using const_iterator = __iterator<node_type, const pair_type>;

	//constructors and destructors:
	bst() noexcept = default; //default ctor

	bst(cmp op): _op{op} {std::cout << "bst custom ctor" << std::endl;}

	bst(const bst& B){

		std::cout << "bst custom copy ctor" << std::endl;
		if( (B.head).get() == nullptr) { return; }
		head = std::make_unique<node_type>(B.head.get(), nullptr);

	}

	bst(bst&& B) noexcept {

		std::cout << "bst custom move ctor" << std::endl;
		head.reset(B.head.release());

	} 

	//operator overloading:
	bst& operator=(const bst& B){ //copy assignment

		std::cout << "bst copy assignment" << std::endl;
		if( (B.head).get() == nullptr) {
			clear();
			return *this;
		}
		head.reset(new node_type{B.head.get(), nullptr});

		return *this;
	}

	bst& operator=(bst&& B) noexcept {//move assignment

		std::cout << "bst move assignment" << std::endl;

		head.reset(B.head.release());

		return *this;
	} 

  //~bst() noexcept {std::cout << "bst dtor " << std::endl;}

std::pair<iterator, bool> insert(const pair_type& x);

std::pair<iterator, bool> insert(pair_type&& x) noexcept ;

template<class... Types>
std::pair<iterator,bool> emplace(Types&&... args);

void clear() noexcept {
	head.reset(nullptr);
}

iterator begin() noexcept {
	node_type * it = head.get();
	if(it != nullptr){
		while(it->_left != nullptr){
			it = (it->_left).get();
		}
	}
	return iterator{it};
}

const_iterator begin() const noexcept {
	node_type * it = head.get();
	if(it != nullptr){
		while(it->_left != nullptr){
			it = (it->_left).get();
		}
	}
	return const_iterator{it};
}

const_iterator cbegin() const noexcept {
	node_type * it = head.get();
	if(it != nullptr){
		while(it->_left != nullptr){
			it = (it->_left).get();
		}
	}
	return const_iterator{it};
}

iterator end() noexcept {
	node_type * it = head.get();
	if(it == nullptr){
		return iterator{nullptr};
	}
	while(it->_right != nullptr){
		it = (it->_right).get();
	}
	return iterator{(it->_right).get()};//returns one past the last element
} 

const_iterator end() const noexcept {
	node_type * it = head.get();
	if(it == nullptr){
		return const_iterator{nullptr};
	}
	while(it->_right != nullptr){
		it = (it->_right).get();
	}
	return const_iterator{(it->_right).get()};
}  

const_iterator cend() const noexcept {
	node_type * it = head.get();
	if(it == nullptr){
		return const_iterator{nullptr};
	}
	while(it->_right != nullptr){
		it = (it->_right).get();
	}
	return const_iterator{(it->_right).get()};
}

iterator find(const kt& x) noexcept ;

const_iterator find(const kt& x) const noexcept ;


void balance() noexcept ;

vt& operator[](const kt& x) noexcept {
	auto tmp = insert(std::make_pair(x, vt{}));

   // comment the next line, it's just for debugging
	std::cout << ((tmp.second == true) ? ( "Pair inserted (with dft vt) since it wasn't there\n" ) : ( "Pair not inserted since it was already there\n" ));

	return (*(tmp.first)).second;
}

vt& operator[](kt&& x) noexcept {
	auto tmp = insert(std::make_pair(std::move(x), vt{}));

  // comment the next line, it's just for debugging
	std::cout << ((tmp.second == true) ? ( "Pair inserted (with dft vt) since it wasn't there\n" ) : ( "Pair not inserted since it was already there\n" ));

	return (*(tmp.first)).second;
}


friend std::ostream& operator<<(std::ostream& os, const bst& x) {
	auto it = x.cbegin();
	auto end = x.cend();
	if(it == end){
		std::cout << "the tree is empty" << std::endl;
	}
	else{
		while(it != end){
			os << it->first << "\t:\t" << it->second << std::endl; 
			++it;
		}
	}
	return os;
}


void erase(const kt& x) noexcept ;

};

#include"bst_functions.hpp"
#include"node.hpp"
#include"iterator.hpp"

#endif
