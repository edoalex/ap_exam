## We keep in header file the following functions

- `~bst()`
- `bst::iterator::operator==`
- `bst::iterator::operator!=`



## Function to be implemented

- `bst`
  - `balance`
  - `emplace`
  - `copy ass`
  - `move ass`
  - `copy ctor`
  - `move ctor`

## Function already implemented

- `bst`
- 
    - 
    
      - `clear`
      - `erase`
      - `dft ctor `	
      - `dtor`
      - `custom ctor` (op)
      - `insert`( reference )
      - `insert`( rvalue )
      - `find` (return it)
      - `find` (return const_it)
      - `begin` (iterator)
      - `begin` (const iterator)
      - `cbegin` 
      - `end` (iterator)
      - `end` (const iterator)
      - `cend` 
      - `operator[]` (reference)
      - `operator[]` (rvalue)
      - `operator<<` 
- `node`
  - 
    - `move ctor`
    - `copy ctor`
- `iterator`
  - 
    - `custom ctor`
    - `operator*`
    - `operator->`
    - `operator++` 
    - `operator++`(int)
    - `operator==`
    - `operator!=`

## Things to be done sooner or later

- insert always calls `insert(T&& x)` and never `insert(const T& x)`: solution tried (not working)

  - both function, called with different names, work
  - created a lvalue and passed, still calls the rvalue function
  - templated unique function and used `std::forward` in `new node{std::forward(x), ptr}`, still not working
  - deleted  `insert(T&& x)`  and tried `insert({1,2})` and `insert(x)`, both working, automatic casted
