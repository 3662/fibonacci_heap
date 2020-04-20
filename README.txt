fibonacci heap:
    have the same functionality as binary heaps but decrease key value function 
    and insertions run in constant amortized time instead of O(log n). it is 
    especially useful in applications where decrease key is called frequently
    and extract min key (and delete) is less frequent. 
    examples of problems where fibonacci heaps outperform binary heaps include 
    computing minimum spanning trees and finding single-source shortest paths 
    among others. 

resources:
    Introduction to Algorithms, Third Ed. Cormen Et Al.

assumptions:
    the code was tested on windows and it is assumed it works on mac and linux
    the code was tested for positive integers 

files:
    each file contain a header with a description. some more detail can be found 
    on comments on the code. 
    there are three independent tests that require files "fibonacci_heap.h" and 
    "node.h" to run.

how to run:
    compile a test file and run it 
    e.g. 
    g++ test_1.cpp -o test_1
    ./test_1 