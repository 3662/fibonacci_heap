/*

Felipe Rodriguez Atuesta
CMPUT 403 project

correctness test:
    - tests insertion and extraction of fib heap using a large input
    - insert randomly generated numbers into fib heap and extract them 
    - compares the extracted numbers in order to a sorted list of those 
      numbers to ensure they are in non-decreasing order 

*/

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm> 
#include "fibonacci_heap.h"

int main() {
    int n = 100000;
    int temp;

    fibonacci_heap f;
    vector<int> v;
    v.reserve(n);

    // inserts n randomly generated numbers  
    for (int i = 0; i < n; ++i) {
        temp = rand();
        f.insert(f.create_node(temp));
        v.push_back(temp);
    }

    sort(v.begin(), v.end());

    for (int i = 0; i < n; ++i) {
        assert(f.extract_min() == v[i]);
    }

    cout << "test completed" << endl;
}