/**
 * @file bst_functions.hpp
 * @author Edoardo Alessandroni 
 * @author Alberto Luvisutto
 * @author Andrea Mecchina 
 * @date 13 February 2020
 * @brief Header containing bst functions implementation.
 */
 
#ifndef __bst_functions_hpp
#define __bst_functions_hpp

#include<iostream> // << operator
#include<memory> // unique pointers
#include<utility> // pair
#include<vector> // vector class
#include"bst.hpp"
#include"node.hpp"
#include"iterator.hpp"

template <typename kt, typename vt, typename cmp>
void bst<kt,vt,cmp>::order(std::vector<std::pair<kt,vt>>& v) noexcept {
	if(v.size() == 1){
		insert(v[0]);
		return;
	}
	else if(v.size() == 2){
		insert(v[0]);
		insert(v[1]);
		return;
	}

	std::vector<std::pair<kt,vt>> w, z;

	for(long unsigned i = 0; i < v.size()/2; ++i){
		w.push_back(v[i]);
	}

	for(long unsigned j = v.size()/2+1; j < v.size(); ++j){
		z.push_back(v[j]);
	}

	insert(v[v.size()/2]);

	order(w);
	order(z);

	return;
}

template <typename kt, typename vt, typename cmp>
std::pair<typename bst<kt,vt,cmp>::iterator, bool> bst<kt,vt,cmp>::insert(const pair_type& x) {
	//std::cout << "insert(const pair_type& x) called" << std::endl;
	if(head == nullptr){
		head.reset(new node_type{x, nullptr});
		return std::make_pair(iterator{head.get()}, true);
	}

	node_type * ptr = head.get();

	while(op_eq(x.first, (ptr->_element).first) == false){

		if(_op(x.first, (ptr->_element).first) == true){

			if(ptr->_left == nullptr){
				(ptr->_left).reset(new node_type{x, ptr});
				return std::make_pair(iterator{(ptr->_left).get()}, true);
			}

			ptr = (ptr->_left).get();

		}else{

			if(ptr->_right == nullptr){
				(ptr->_right).reset(new node_type{x, ptr});
				return std::make_pair(iterator{(ptr->_right).get()}, true);
			}

			ptr = (ptr->_right).get();
		}
	}
	//std::cout << "node not inserted, key: " << x.first << " is already present" << std::endl;
	return std::make_pair(iterator{ptr}, false);
}

template <typename kt, typename vt, typename cmp>
std::pair<typename bst<kt,vt,cmp>::iterator, bool> bst<kt,vt,cmp>::insert(pair_type&& x) noexcept {
	//std::cout << "insert(pair_type&& x) called" << std::endl;
	if(!head){
	    head.reset(new node_type{std::move(x), nullptr});
	    return std::make_pair(iterator{head.get()}, true);
	}

	node_type * ptr = head.get();

	while(op_eq(x.first, (ptr->_element).first) == false){

		if(_op(x.first, (ptr->_element).first) == true){

			if(ptr->_left == nullptr){
				(ptr->_left).reset(new node_type{std::move(x), ptr});

				return std::make_pair(iterator{(ptr->_left).get()}, true);
			}
			ptr = (ptr->_left).get();
		}else{

			if(ptr->_right == nullptr){

				(ptr->_right).reset(new node_type{std::move(x), ptr});
				return std::make_pair(iterator{(ptr->_right).get()}, true);
			}
			ptr = (ptr->_right).get();
		}

	}
	//std::cout << "node not inserted, key: " << x.first << " is already present" << std::endl;
	return std::make_pair(iterator{ptr}, false); 
}

template <typename kt, typename vt, typename cmp>
template<class... Types>
std::pair<typename bst<kt,vt,cmp>::iterator,bool> bst<kt,vt,cmp>::emplace(Types&&... args){
	//std::cout << "inside emplace" << std::endl;
	std::unique_ptr<node_type> buffer = std::make_unique<node_type>(std::forward<Types>(args)...);

	//std::cout << "key = "<< (buffer->_element).first << " value = " << (buffer->_element).second << std::endl;
	auto possible_node = buffer.get();
	auto it = find((possible_node->_element).first);
	if(it._current != nullptr){
		//std::cout << "destructing the node" << std::endl;
		buffer.reset();
		return std::make_pair(it, false);
	}

	//the node needs to be inserted
	if(!head){
		//std::cout << "the head is empty" << std::endl;
		head.reset(buffer.release());
		return std::make_pair(iterator{head.get()}, true);
	}

	//the tree is not empty
	node_type * ptr = head.get();
	while(true){
		if(_op((possible_node->_element).first, (ptr->_element).first) == true){ //needs to go left
			if(ptr->_left == nullptr){
				//no left child
				(ptr->_left).reset(buffer.release());
				possible_node->_parent = ptr;
				return std::make_pair(iterator{possible_node}, true);
			}
			ptr = (ptr->_left).get();
		}else{

			if(ptr->_right == nullptr){

				(ptr->_right).reset(buffer.release());

				possible_node->_parent = ptr;

				return std::make_pair(iterator{possible_node}, true);
			}

			ptr = (ptr->_right).get();
		}
	}
}

template <typename kt, typename vt, typename cmp>
typename bst<kt,vt,cmp>::iterator bst<kt,vt,cmp>::find(const kt& x) noexcept {

    //std::cout << "greetings from iterator find(...)" << std::endl;
	if(!head){
      	//std::cout << "the tree is empty" << std::endl;
		return end();
	}
	node_type * tmp = head.get();
	while(op_eq(x,(tmp->_element).first) == false){
		if(_op(x,(tmp->_element).first) == true){
			if(tmp->_left == nullptr){
	  			//std::cout << "node with key " << x << " not found in the tree" << std::endl;
				return end();
			}
			tmp = (tmp->_left).get();
		} else {
			if(tmp->_right == nullptr){
	  			//std::cout << "node with key " << x << " not found in the tree" << std::endl;
				return end();
			}
			tmp = (tmp->_right).get();
		}
	}

	//std::cout << "node with key " << x << " found in the tree" << std::endl;
	return iterator{tmp};
}

template <typename kt, typename vt, typename cmp>
typename bst<kt,vt,cmp>::const_iterator bst<kt,vt,cmp>::find(const kt& x) const noexcept {
  	//std::cout << "greetings from const_iterator find(...)" << std::endl;

	if(!head){
		//std::cout << "the tree is empty" << std::endl;
		return cend();
	}

	node_type * tmp = head.get();

	while(op_eq(x,(tmp->_element).first) == false){

		if(_op(x,(tmp->_element).first) == true){

			if(tmp->_left == nullptr){
				//std::cout << "node with key " << x << " not found in the tree" << std::endl;
				return end();
			}

			tmp = (tmp->_left).get();
		} else {

			if(tmp->_right == nullptr){

				//std::cout << "node with key " << x << " not found in the tree" << std::endl;
				return end();

			}
			tmp = (tmp->_right).get();
		}
	}

	//std::cout << "node with key " << x << " found in the tree" << std::endl;
	return const_iterator{tmp};
}

template <typename kt, typename vt, typename cmp>
void bst<kt,vt,cmp>::balance() noexcept {

	auto start = begin();
	if(start._current == nullptr){
		//std::cout << "the tree is empty" << std::endl;
		return;
	}
	auto stop = end();

	std::vector<std::pair<kt,vt>> v;
	
	while(start != stop){
		v.push_back(*start);
		++start;
	}

	clear();

	order(v);

	return;
}

template <typename kt, typename vt, typename cmp>
void bst<kt,vt,cmp>::erase(const kt& x) noexcept {
	iterator it = find(x);                                                                                                                         

	auto me = it._current;

	if(!me){
		//std::cout << "node with key = " << x << "not present in the tree" << std::endl;
		return;
	}

    //naming an object for a cleaner code
	auto ave = me->_parent;

    if(me->_left == nullptr && me->_right == nullptr){ //both children nullptr                       
    	if(me == head.get()){
    		head.reset(nullptr);
    		return;
    	} else {
    		((ave->_right).get() == me) ? (ave->_right = nullptr) : (ave->_left = nullptr);
    	}


    } else if ( (me->_left != nullptr) != (me->_right != nullptr) ) {  //just one child  
      	//cut and paste that bow                                          
    	node_type * tmp;
    	if( me->_right != nullptr ){
    		tmp = me->_right.release();
    	}
    	else{
    		tmp = me->_left.release();
    	}
      	//std::cout << "just released node with key: " << (tmp->_element).first << std::endl;
    	if( ave == nullptr ) {
    		head.reset(tmp);
    		head->_parent = nullptr;
    	}
    	else {
    		if( (ave->_left).get() == me ){
    			ave->_left.reset(tmp);
    			(ave->_left)->_parent = ave;
    		}
    		else{
    			ave->_right.reset(tmp);
    			(ave->_right)->_parent = ave;
    		}
    	}

    } else { //I have both children 

    	auto next = (++it)._current;
    	//std::cout << "next key = " << (next->_element).first << std::endl;
    	auto next_parent = next->_parent;
    	//std::cout << "next_parent key = " << (next_parent->_element).first << std::endl;

      	//if first_right = next, which means, next_parent = me  (pathological case)
    	if ( next_parent == me ){
    		auto tmp = (me->_left).release();
    		(me->_right).release();
    		if( ave == nullptr){
    			head.reset(next);
    			next->_parent = nullptr;
    		}
    		else{
    			if( (ave->_right).get() == me ){
    				(ave->_right).reset(next);
    			}
    			else{
    				(ave->_left).reset(next);
    			}
    			next->_parent = ave;
    		}
    		(next->_left).reset(tmp);
    		tmp->_parent = next;
    		return; 
    	}

      	//(non pathological case)
      	//step 1 of 3 (replace me with next)
    	(next_parent->_left).release();
    	std::unique_ptr<node_type> saver = nullptr;
      	//if I'm root
    	if( ave == nullptr ){
    		next->_parent = nullptr;
    		saver.reset(head.release());
    		head.reset(next);
    	}else{ //if I'm not root
    		//I'm right son
    		if( (ave->_right).get() == me ){
    			saver.reset((ave->_right).release());
    			(ave->_right).reset(next);
    		//I'm left son
    		}else{
    			saver.reset((ave->_left).release());
    			(ave->_left).reset(next);
    		}
    		next->_parent = ave;
    		me->_parent = nullptr;
    	}
    	
    	//step 2 of 3 (stick right prole of me)
    	auto to_stick = (me->_right).release();
    	auto sub = next;
    	while( next->_right != nullptr) { 
    		next = (next->_right).get(); 
    	}

    	(next->_right).reset(to_stick);
    	to_stick->_parent = next;

    	//step 3 of 3 (stick left prole of me)
    	(sub->_left).reset( (me->_left).release() );
    	(sub->_left)->_parent = sub;

    	//the node to be erased (me) is eliminated
    	saver.reset();
    }
}

#endif
