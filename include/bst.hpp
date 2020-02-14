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
	
	/** @brief Comparison operator for the binary search tree. */
	
	cmp _op;
	
	/** Alias to make names shorter and intuitive. */
	
	using node_type = node<std::pair<const kt, vt>>;
	
	/** Root node of the binary search tree. */
	
	std::unique_ptr<node_type> head;

	/**
	 * @brief Checks if the keys are equal or not.
	 * @param x The first key to be compared.
	 * @param y The second key to be compared.
	 * @return True if the two keys are equal, else false.
	 */

	bool op_eq(const kt& x,const kt& y) const noexcept {
		return (_op(x, y) == false && _op(y, x) == false) ? true : false;
	}

	/**
	 * @brief Auxiliary function needed by balance.
	 * @param v A vector of pairs in ascending order.
	 *
	 * Iterative function inserting in the tree the central 
	 * element and subdivides the vector in two halves, then
	 * it calls itself on these two halves.
	 */

	void order(std::vector<std::pair<kt,vt>>& v) noexcept;

public:

	/** Alias to make names shorter and intuitive. */

	using pair_type = std::pair<const kt, vt>;
	
	/** Alias to make names shorter and intuitive. */
	
	using iterator = __iterator<node_type, pair_type>;	
	
	/** Alias to make names shorter and intuitive. */
	
	using const_iterator = __iterator<node_type, const pair_type>;

	/**
	 * @brief Default constructor for binary search tree.
	 */
	 
	bst() noexcept = default;
	
	/**
	 * @brief Custom constructor for binary search tree.
	 * @param op Comparison operator between nodes.
	 */

	bst(cmp op): _op{op} {
		//std::cout << "bst custom ctor" << std::endl;
	}

	/**
	 * @brief Copy constructor for binary search tree.
	 * @param B The binary search tree to be copied into a new one.
	 * 
	 * The method performs a deep copy of the tree 
	 * calling a custom constructor of the node.
	 */

	bst(const bst& B){

		//std::cout << "bst custom copy ctor" << std::endl;
		if( (B.head).get() == nullptr) { return; }
		head = std::make_unique<node_type>(B.head.get(), nullptr);

	}

	/**
	 * @brief Move constructor for binary search tree.
	 * @param B The binary search tree to be moved into a new one.
	 */

	bst(bst&& B) noexcept {

		//std::cout << "bst custom move ctor" << std::endl;
		head.reset(B.head.release());

	} 

	/**
	 * @brief Copy assignment for binary search tree.
	 * @param B The binary search tree to be copied into an existing one.
	 * @return bst& The modified existing tree.
	 */
	 
	bst& operator=(const bst& B){

		//std::cout << "bst copy assignment" << std::endl;
		if( (B.head).get() == nullptr) {
			clear();
			return *this;
		}
		head.reset(new node_type{B.head.get(), nullptr});

		return *this;
	}

	/**
	 * @brief Move assignment for binary search tree.
	 * @param B The binary search tree to be moved into an existing one.
	 * @return bst& The modified existing tree.
	 */

	bst& operator=(bst&& B) noexcept {

		//std::cout << "bst move assignment" << std::endl;

		head.reset(B.head.release());

		return *this;
	}
	
	/**
	 * @brief Inserts a new node in the binary search tree.
	 * @param x The pair key and value to be inserted.
	 * @return std::pair<iterator, bool> A pair of an iterator and a bool.
	 *  
	 * The iterator of the pair points to the inserted node or the previously
	 * existent node with the same key if one is present. If the insertion
	 * were successful the bool is true, else false. The pair is copied into
	 * the node.
	 */

	std::pair<iterator, bool> insert(const pair_type& x);

	/**
	 * @brief Inserts a new node in the binary search tree.
	 * @param x The pair key and value to be inserted.
	 * @return std::pair<iterator, bool> A pair of an iterator and a bool.
	 *  
	 * The iterator of the pair points to the inserted node or the previously
	 * existent node with the same key if one is present. If the insertion
	 * were successful the bool is true, else false. The pair is moved into
	 * the node.
	 */

	std::pair<iterator, bool> insert(pair_type&& x) noexcept;

	/**
	 * @brief Inserts a new node in the binary search tree.
	 * @tparam Types Types of the variable number of parameters.
	 * @param args Variable number of parameters.
	 * @return std::pair<iterator, bool> A pair of an iterator and a bool.
	 *  
	 * A node is created. If the key is already present in the tree,
	 * the node is destroyed, else it's inserted.
	 */

	template<class... Types>
	std::pair<iterator,bool> emplace(Types&&... args);

	/**
	 * @brief Clears the tree freeing the memory of the taken by nodes.
	 */

	void clear() noexcept {
		head.reset(nullptr);
	}

	/**
	 * @brief Used to begin an iteration on the binary search tree.
	 * @return iterator An iterator to the leftmost node of the tree.
	 */

	iterator begin() noexcept {
		node_type * it = head.get();
		if(it != nullptr){
			while(it->_left != nullptr){
				it = (it->_left).get();
			}
		}
		return iterator{it};
	}

	/**
	 * @brief Used to begin an iteration on the binary search tree.
	 * @return const_iterator A constant iterator to the leftmost node of the tree.
	 */

	const_iterator begin() const noexcept {
		node_type * it = head.get();
		if(it != nullptr){
			while(it->_left != nullptr){
				it = (it->_left).get();
			}
		}
		return const_iterator{it};
	}

	/**
	 * @brief Used to begin an iteration on the binary search tree.
	 * @return const_iterator A constant iterator to the leftmost node of the tree.
	 *
	 * Implemented to assure the user of returning a constant iterator.
	 */

	const_iterator cbegin() const noexcept {
		node_type * it = head.get();
		if(it != nullptr){
			while(it->_left != nullptr){
				it = (it->_left).get();
			}
		}
		return const_iterator{it};
	}

	/**
	 * @brief Used to finish an iteration on the binary search tree.
	 * @return iterator A iterator to one past the rightmost node of the tree.
	 */

	iterator end() noexcept {
		node_type * it = head.get();
		if(it == nullptr){
			return iterator{nullptr};
		}
		while(it->_right != nullptr){
			it = (it->_right).get();
		}
		return iterator{(it->_right).get()};
	} 

	/**
	 * @brief Used to finish an iteration on the binary search tree.
	 * @return iterator A constant iterator to one past the rightmost node of the tree.
	 */

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

	/**
	 * @brief Used to begin an iteration on the binary search tree.
	 * @return const_iterator A constant iterator to one past the rightmost node of the tree.
	 *
	 * Implemented to assure the user of returning a constant iterator.
	 */

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

	/**
	 * @brief Used to find a node inside the tree.
	 * @param x The key of the node to be found.
	 * @return iterator An iterator to the node if found, else to end().
	 */

	iterator find(const kt& x) noexcept ;

	/**
	 * @brief Used to find a node inside the tree.
	 * @param x The key of the node to be found.
	 * @return const_iterator A constant iterator to the node if found, else to end().
	 */

	const_iterator find(const kt& x) const noexcept ;

	/**
	 * @brief Balances the tree.
	 * 
	 * Creates a sorted vector of pairs key and value, clears the tree
	 * and passes the vector to the previously defined private function
	 * order.
	 */

	void balance() noexcept ;

	/**
	 * @brief Operator [] overloading to access a node value in the tree or insert a new one.
	 * @param x The key of the node whose value should be accessed.
	 * @return vt& A reference to the value of the accessed node.
	 *
	 * It calls the copy implementation of the insert function.
	 */

	vt& operator[](const kt& x) noexcept {
		auto tmp = insert(std::make_pair(x, vt{}));

		//std::cout << ((tmp.second == true) ? ( "Pair inserted (with dft vt) since it wasn't there\n" ) : ( "Pair not inserted since it was already there\n" ));

		return (*(tmp.first)).second;
	}
	
	/**
	 * @brief Operator [] overloading to access a node value in the tree or insert a new one.
	 * @param x The key of the node whose value should be accessed.
	 * @return vt& A reference to the value of the accessed node.
	 *
	 * It calls the move implementation of the insert function.
	 */

	vt& operator[](kt&& x) noexcept {
		auto tmp = insert(std::make_pair(std::move(x), vt{}));

		//std::cout << ((tmp.second == true) ? ( "Pair inserted (with dft vt) since it wasn't there\n" ) : ( "Pair not inserted since it was already there\n" ));

		return (*(tmp.first)).second;
	}

	/**
	 * @brief Operator << overloading to print the tree according to the keys order.
	 * @param os The output stream to which the strings to be printed are appended.
	 * @param x The tree to be printed.
	 * @return std::ostream& The output stream to which strings have been appended.
	 *
	 * It calls cbegin() and cend() to be sure the tree is unchanged by the iterators.
	 */

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
	
	/**
	 * @brief Removes a node from the tree if present.
	 * @param x The key of the node to be removed.
	 *
	 * After removing a node the ordering of the
	 * tree is preserved. 
	 */
	 
	void erase(const kt& x) noexcept;

};

#include"bst_functions.hpp"
#include"node.hpp"
#include"iterator.hpp"

#endif
