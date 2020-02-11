#ifndef __bst_hpp
#define __bst_hpp

#include<memory>
#include<utility>
#include<iostream>
#include<vector>


template <typename kt, typename vt, typename cmp = std::less<kt>>
class bst{

  template<typename node_type, typename pair_type>
	class __iterator;

  template <typename pair_type>
	struct node;

	cmp _op;
	
	using node_type = node<std::pair<const kt, vt>>;
	
	std::unique_ptr<node_type> head;

	bool op_eq(const kt& x,const kt& y){
		return (_op(x, y) == false && _op(y, x) == false) ? true : false;
	}

	void order(std::vector<std::pair<kt,vt>>& v){

		if(v.size() == 1){
			insert(v.at(0));
			return;
		}
		else if(v.size() == 2){
			insert(v.at(0));
			insert(v.at(1));
			return;
		}
	/*else if(v.size() == 0){
		return;
	}*/

		std::vector<std::pair<kt,vt>> w, z;

		for(long unsigned i = 0; i < v.size()/2; ++i){
			w.push_back(v.at(i));
		}

		for(long unsigned j = v.size()/2+1; j < v.size(); ++j){
			z.push_back(v.at(j));
		}

		insert(v.at(v.size()/2));

		order(w);
		order(z);

		return;
	}

	/*void recursive_copy_tree(node_type * ptr){
		node_type * left_child = (ptr->_left).get();
		node_type * right_child = (ptr->_right).get();
		insert(ptr->_element);
		if(left_child != nullptr){
			recursive_copy_tree(left_child);
		}

		if(right_child != nullptr){
			recursive_copy_tree(right_child);
		}

		return;
	}*/

public:

	using pair_type = std::pair<const kt, vt>;
  //using pair_type = typename node_type::pair_type;
	using iterator = __iterator<node_type, pair_type>;	
	using const_iterator = __iterator<node_type, const pair_type>;

  //constructors and destructors:
  //note that these constructors can go only in the header if they are default constructors!!
  bst() noexcept = default; //default ctor
  bst(cmp op): _op{op} {std::cout << "bst custom ctor" << std::endl;}
  
  bst(const bst& B){

  	std::cout << "bst custom copy ctor" << std::endl;

  	head = std::make_unique<node_type>(B.head.get(), nullptr);
  	
  }

  bst(bst&& B){

  	std::cout << "bst custom move ctor" << std::endl;

  	head.reset(B.head.release());

  } 

  //operator overloading:
  //do we need to put in the headers also the operator overloading? Probably yes, they are still functions
  bst& operator=(const bst& B){ //copy assignment

  	std::cout << "bst copy assignment" << std::endl;
  	
  	head.reset(new node_type{B.head.get(), nullptr});

  	return *this;
  }

  bst& operator=(bst&& B){//move assignment

  	std::cout << "bst move assignment" << std::endl;

  	head.reset(B.head.release());

  	return *this;
  } 

  ~bst() {std::cout << "bst dtor " << std::endl;}
  
std::pair<iterator, bool> insert(const pair_type& x){ //check if it can be optimized
	std::cout << "insert(const pair_type& x) called" << std::endl;
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
	return std::make_pair(iterator{nullptr}, false);
}

std::pair<iterator, bool> insert(pair_type&& x){ //check if it can be optimized
	std::cout << "insert(pair_type&& x) called" << std::endl;
	if(!head){
	    head.reset(new node_type{std::move(x), nullptr}); // maybe nullprt = make_shared(nullptr)
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
	std::cout << "node not inserted, key: " << x.first << " is already present" << std::endl;
	return std::make_pair(iterator{nullptr}, false);
}

template<class... Types>
std::pair<iterator,bool> emplace(Types&&... args){
	//std::unique_ptr<node_type> buffer = std::make_unique<node_type>(std::forward<Types>(args)...);
	//NEED TO BE ADDED A CONSTRUCTOR THAT RECEIVE ONLY THE VALUES OF KT AND VT?
	//or we can initialize it with nullptr as a parent, and then can change it if we 
	//find it can be inserted?
	//with the following line instead:
	std::cout << "inside emplace" << std::endl;
	std::unique_ptr<node_type> buffer = std::make_unique<node_type>(std::forward<Types>(args)...);

	std::cout << "key = "<< (buffer->_element).first << " value = "<< (buffer->_element).second << std::endl;
	auto possible_node = buffer.get();
	auto it = find((possible_node->_element).first);
	if(it._current != nullptr){
		std::cout << "destructing the node" << std::endl;
		buffer.reset();
		return std::make_pair(iterator{nullptr}, false);
	}
	//the node needs to be inserted
	if(!head){ //the tree is empty
		std::cout << "the head is empty" << std::endl;
		auto a = buffer.release();
		head.reset(a);
		std::cout << "the head points to " << head.get() <<  std::endl 
		<< 	" parent pointer: " << (head.get())->_parent <<  std::endl 
		<< " left pointer: " << (head->_left).get() <<  std::endl 
		<< " right pointer: " << (head->_right).get() <<  std::endl;

		return std::make_pair(iterator{head.get()}, true);
	}
  	//the tree is not empty
	node_type * ptr = head.get();



	while(true){

  		if(_op((possible_node->_element).first, (ptr->_element).first) == true){ //devo andare a sx

  			if(ptr->_left == nullptr){ //non c'è il figlio
  				
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

void clear(){
	head.reset(nullptr);
}

iterator begin(){
	node_type * it = head.get();
	if(it != nullptr){
		while(it->_left != nullptr){
			it = (it->_left).get();
		}
	}
	return iterator{it};
}

const_iterator begin() const{
	node_type * it = head.get();
	if(it != nullptr){
		while(it->_left != nullptr){
			it = (it->_left).get();
		}
	}
	return const_iterator{it};
}

const_iterator cbegin() const{
	node_type * it = head.get();
	if(it != nullptr){
		while(it->_left != nullptr){
			it = (it->_left).get();
		}
	}
	return const_iterator{it};
}

iterator end(){
	node_type * it = head.get();
	if(it == nullptr){
		return iterator{nullptr};
	}
	while(it->_right != nullptr){
		it = (it->_right).get();
	}
	return iterator{(it->_right).get()};//returns one past the last element
} 

const_iterator end() const{
	node_type * it = head.get();
	if(it == nullptr){
		return const_iterator{nullptr};
	}
	while(it->_right != nullptr){
		it = (it->_right).get();
	}
	return const_iterator{(it->_right).get()};
}  

const_iterator cend() const{
	node_type * it = head.get();
	if(it == nullptr){
		return const_iterator{nullptr};
	}
	while(it->_right != nullptr){
		it = (it->_right).get();
	}
	return const_iterator{(it->_right).get()};
}

iterator find(const kt& x){

	  // std::cout << "greetings from iterator find(...)" << std::endl;

	if(!head){
		std::cout << "the tree is empty" << std::endl;
		return iterator{nullptr}; 
	}

	node_type * tmp = head.get();

	while(op_eq(x,(tmp->_element).first) == false){

		if(_op(x,(tmp->_element).first) == true){

			if(tmp->_left == nullptr){
		// std::cout << "node with key " << x << " not found in the tree" << std::endl;
				return end();
			}

			tmp = (tmp->_left).get();

		} else {

			if(tmp->_right == nullptr){
		// std::cout << "node with key " << x << " not found in the tree" << std::endl;
				return end();
			}

			tmp = (tmp->_right).get();

		}

	}

	  // std::cout << "node with key " << x << " found in the tree" << std::endl;
	return iterator{tmp};

}

const_iterator find(const kt& x) const{
	std::cout << "greetings from const_iterator find(...)" << std::endl;

	if(!head){
		std::cout << "the tree is empty" << std::endl;
		return const_iterator{nullptr};
	}

	node_type * tmp = head.get();

	while(op_eq(x,(tmp->_element).first) == false){

		if(_op(x,(tmp->_element).first) == true){

			if(tmp->_left == nullptr){
				std::cout << "node with key " << x << " not found in the tree" << std::endl;
				return end();
			}

			tmp = (tmp->_left).get();
		} else {

			if(tmp->_right == nullptr){

				std::cout << "node with key " << x << " not found in the tree" << std::endl;
				return end();

			}
			tmp = (tmp->_right).get();
		}
	}

	std::cout << "node with key " << x << " found in the tree" << std::endl;
	return const_iterator{tmp};
}


void balance(){

	auto start = begin();
	if(start._current == nullptr){
		std::cout << "The tree is empty" << std::endl;
		return;
	}
	auto stop = end();

	std::vector<std::pair<kt,vt>> v;
	
	while(start != stop){
		v.push_back(*start); //try *it++; also, maybe the reference is not good
		++start;
	}

	clear();

	order(v);

	return;
}

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
			//vt no_value{};
		auto pair = insert(std::make_pair(std::move(x), vt{}));
		std::cout << "pair inserted" << std::endl;
		return (*(pair.first)).second;
	}
	return (*tmp).second;
}

template <typename KT, typename VT, typename CMP>
friend std::ostream& operator<<(std::ostream& os, const bst<KT, VT, CMP>& x){
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


void erase(const kt& x){
	iterator it = find(x);                                                                                                                         

	auto me = it._current;

	if(!me){
		std::cout << "node with key = " << x << " not present in the tree" << std::endl;
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


    } else if ( (me->_left != nullptr) != (me->_right != nullptr) ) {  // just one child  
      //cut and paste that bow                                          
    	node_type * tmp;
    	if( me->_right != nullptr ){
    		tmp = me->_right.release();
    	}
    	else{
    		tmp = me->_left.release();
    	}
      // std::cout << "I've just released node with key: " << (tmp->_element).first << std::endl;
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

    } else { // I have both children 

    	auto next = (++it)._current;
    	std::cout << "next key = " << (next->_element).first << std::endl;
    	auto next_parent = next->_parent;
    	std::cout << "next_parent key = " << (next_parent->_element).first << std::endl;

      // if first_right = next    ==    next_parent = me  (pathological case)
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

      // (non pathological case)
      // step 1 of 3 (replace me with next)
    	(next_parent->_left).release();
      // if I'm root
    	if( ave == nullptr ){
    		next->_parent = nullptr;
    		head.release();
    		head.reset(next);
    	}else{ // if I'm not root
	// I'm right son
    	if( (ave->_right).get() == me ){
    		(ave->_right).release();
    		(ave->_right).reset(next);
		// I'm left son
    	}else{
    		(ave->_left).release();
    		(ave->_left).reset(next);
    	}
    	next->_parent = ave;
			me->_parent = nullptr; // do we really need it? 
		}

      // step 2 of 3 (stick right prole of me)
		auto to_stick = (me->_right).release();
	      //(me->_right).release();
		auto sub = next;
		while( next->_right != nullptr) { 
			next = (next->_right).get(); 
		}
		(next->_right).reset(to_stick);
		to_stick->_parent = next;

	      // step 3 of 3 (stick left prole of me)
	      //auto prole = (me->_left).release()
	      //(next->_left).reset(prole);
		(sub->_left).reset( (me->_left).release() );
		(sub->_left)->_parent = sub;

		//delete me using a unique pointer; we didn't want to change the whole algorithm and we didn't want to call the destuctor by hand ("NEVER EVER EVER EVER EVER call the destructor by hand" cit: A.S.);
		//please forgive us
		std::unique_ptr<node_type> deleter = nullptr;
		deleter.reset(me);
		deleter.reset();

	}
}

};




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

	node() = delete;

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
		std::cout << "key from old ctor = " << element.first << " value from old ctor = " << element.second << std::endl;
	} //removed a const before node || do I need to write const node * parent?
	
	node(const pair_type& element, node * parent) : _element{element}, _parent{parent} {} //custom ctor

	node(kt&& k, vt&& v) noexcept : _element{std::make_pair<kt,vt>(std::move(k), std::move(v))}	{
		std::cout << "key from new ctor = " << k << " value from new ctor = " << v << std::endl;
		//node(std::make_pair<kt,vt>(std::move(k),std::move(v)), nullptr);
	} 

    ~node() {std::cout << "node dtor with key " << (this->_element).first << std::endl;} //do we need to delete the raw pointer??
};

template<typename kt, typename vt, typename cmp>
template<typename node_type, typename pair_type>
class bst<kt, vt, cmp>::__iterator{//do we implement a class or a struct? He implemented a class also in the linked list
	
	node_type * _current;


	friend class bst<kt,vt,cmp>;
	//incomplete list of methods (not working for default template conflict)
	/*friend vt& bst<kt,vt,cmp>::operator[](const kt& x);
	friend vt& bst<kt,vt,cmp>::operator[](kt&& x);
	friend std::pair<bst<kt,vt,cmp>::iterator, bool> bst<kt,vt,cmp>::insert(pair_type&& x);
	friend std::pair<bst<kt,vt,cmp>::iterator, bool> bst<kt,vt,cmp>::insert(const pair_type& x);
	friend bst<kt,vt,cmp>::iterator bst<kt,vt,cmp>::find(const kt& x);
	friend bst<kt,vt,cmp>::const_iterator bst<kt,vt,cmp>::find(const kt& x);*/
	
	explicit __iterator(node_type * x) noexcept: _current{x} {
		//std::cout << "iterator custom ctor" << std::endl;
	}

public:

	using reference = pair_type&;
	using pointer = pair_type*;
	using difference_type = std::ptrdiff_t;
	using iterator_category = std::forward_iterator_tag;

    //__iterator(){std::cout << "iterator default ctor" << std::endl;}


	//~__iterator(){std::cout << "iterator dtor" << std::endl;}

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
		//std::cout<< "pre incremenent" << std::endl;
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


	__iterator operator++(int) noexcept{
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
