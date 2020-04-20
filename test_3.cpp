/*

Felipe Rodriguez Atuesta
CMPUT 403 project

time complexity and correctness test:
    - generates a large number of random integers to be inserted and extracted 
      in both a fibonacci heap and a priority queue (binary heap)
    - then compares the ammount of time each data structure took to insert all 
      integers  
    - fib heap insertion should take amortized O(1)
    - priority queue is implemented using binary heaps, so insertion takes 
      O(log n) in the worst case
    - then tests correcness by extracting all integers in both heaps and 
      comparing them 

*/

#include <iostream>
#include <queue>
#include <cassert>
#include <chrono>
#include "fibonacci_heap.h"

int main() {
    int n = 1000000;

    fibonacci_heap f;
    priority_queue<int, vector<int>, greater<int>> pq;

    vector<int> test;
    test.reserve(n);

    // inserts n randomly generated numbers to test
    for (int i = 0; i < n; ++i) {
        test.push_back(rand());
    }

    // prints the amount of time it takes each to insert and extract all 

    auto start_fib = chrono::steady_clock::now();
    // insertion
    for (int i = 0; i < n; ++i) {
        f.insert(f.create_node(test[i]));
    }
    auto end_fib = chrono::steady_clock::now();

    cout << "fibonacci heap time to insert: "
         << chrono::duration_cast<chrono::milliseconds>(end_fib - start_fib).count() 
         << " ms" << endl;

    auto start_bin = chrono::steady_clock::now();
    // insertion
    for (int i = 0; i < n; ++i) {
        pq.push(test[i]);
    }
    auto end_bin = chrono::steady_clock::now();

    cout << "binary heap time to insert:    "
         << chrono::duration_cast<chrono::milliseconds>(end_bin - start_bin).count() 
         << " ms" << endl;

    cout << "correctness test start" << endl;

    for (int i = 0; i <n; ++i) {
        assert(f.extract_min() == pq.top());
        pq.pop();
    }

    cout << "correctness test end" << endl;
}