#include"bst.hpp"
#include<iostream>
#include<chrono>
#include<random>
#include<algorithm>
#include<vector>

#define n_step 5000
#define max_n  1000000
#define sample_size 2000

void compare_type(){

  std::vector<int> v_i;
  std::vector<double> v_d;
  std::vector<int> keys_i;
  std::vector<double> keys_d;
  
  for(unsigned int i{0}; i<max_n; i++)
    v_i.push_back(i);
  std::random_shuffle(std::begin(v_i), std::end(v_i));

  std::uniform_real_distribution<double> unif( 0.0, 1000.0 );
  std::default_random_engine re;
  for(unsigned int i{0}; i<max_n; i++)
    v_d.push_back( unif(re) );
  
  bst<int,int> tree_i{};
  bst<double,double> tree_d{};
  
  auto t0 = std::chrono::high_resolution_clock::now();
  auto t1 = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0);
  
  for(int i{0}; i<max_n; i += n_step){

    // add x_step elements to containers
    for(int j{0}; j<n_step; ++j){
      tree_i.insert({ v_i[ j+i ] , v_i[ j+i ] });
      keys_i.push_back( v_i[ j+i ] );
      tree_d.insert({ v_d[ j+i ] , v_d[ j+i ] });
      keys_d.push_back( v_d[ j+i ] );
    }
    
    // balance the trees
    tree_i.balance();
    tree_d.balance();
    
    // measure finding `sample` random elements 
    std::random_shuffle(std::begin(keys_i), std::end(keys_i));
    std::random_shuffle(std::begin(keys_d), std::end(keys_d));
    
    // measure tree_i
    t0 = std::chrono::high_resolution_clock::now();

    for(auto waldo{0}; waldo<sample_size ; ++waldo){
      tree_i.find( keys_i[waldo] );
    }
    
    t1 = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0);
    std::cout << elapsed.count()/sample_size << "\t";
    //std::cout << "Integer tree takes \t\t" << elapsed.count()/sample_size << "\tns\n";
    
    // measure tree_d
    t0 = std::chrono::high_resolution_clock::now();

    for(auto waldo{0}; waldo<sample_size ; ++waldo){
      tree_d.find( keys_d[waldo] );
    }

    t1 = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0);
    std::cout << elapsed.count()/sample_size << "\t\n";
    //std::cout << "Double tree takes \t\t" << elapsed.count()/sample_size << "\tns\n\n";
      
  }
}



int main(){

  try {

    compare_type();
    
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;

  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n" << std::endl;
    return 2;
  }

  return 0;
}
