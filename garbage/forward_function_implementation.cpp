//remove other two insert functions
//inside of the class:

template<typename OT>
std::pair<iterator, bool> insert(OT&& x);


//outside of the class:

template<typename kt, typename vt, typename cmp>
template<typename OT>
std::pair<typename bst<kt,vt,cmp>::iterator, bool> bst<kt, vt, cmp>::insert(OT&& x){
	std::cout << "insert(pair_type&& x) called" << std::endl;
		if (!head){
			head.reset(new node_type{std::forward<OT>(x), nullptr}); // maybe nullprt = make_shared(nullptr)
			return std::make_pair(iterator{head.get()}, true);
		}

		node_type * ptr = head.get();

		while(op_eq(x.first, (ptr->_element).first) == false){

			if(_op(x.first, (ptr->_element).first) == true){

				if(ptr->_left == nullptr){
					(ptr->_left).reset(new node_type{std::forward<OT>(x), ptr});

					return std::make_pair(iterator{(ptr->_left).get()}, true);
				}
				ptr = (ptr->_left).get();
			}else{

				if(ptr->_right == nullptr){

				  	(ptr->_right).reset(new node_type{std::forward<OT>(x), ptr});
					return std::make_pair(iterator{(ptr->_right).get()}, true);
				}
				ptr = (ptr->_right).get();
			}
			
		}
		std::cout << "node not inserted, key: " << x.first << " is already present" << std::endl;
		return std::make_pair(iterator{nullptr}, false);
	}
