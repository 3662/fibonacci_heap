/*

Felipe Rodriguez Atuesta
CMPUT 403 project

correctness test:
    - tests basic functionality of methods with small inputs

*/

#include <iostream>
#include <cassert>
#include "fibonacci_heap.h"

int main() {

    node * tst;
    node * ntst;

    // init 
    fibonacci_heap f;
    assert(f.get_nodes() == 0);
    assert(f.get_min_key() == NULL);

    // insert and get functions
    f.insert(f.create_node(3));
    assert(f.get_nodes() == 1);
    assert(f.get_min_key()->key == 3);

    f.insert(f.create_node(2));
    assert(f.get_nodes() == 2);
    assert(f.get_min_key()->key == 2);

    f.insert(f.create_node(2));
    f.insert(f.create_node(29));

    // left and right pointers of nodes
    tst = f.get_min_key();

    while (true) {
        cout << tst->key << " ";
        tst = tst->right;
        if (tst == f.get_min_key()) {
            break;
        }
    }
    cout << endl;

    tst = f.get_min_key();
    while (true) {
        cout << tst->key << " ";
        tst = tst->left;
        if (tst == f.get_min_key()) {
            break;
        }
    }
    cout << endl;

    // change of min node 
    f.insert(f.create_node(1));

    tst = f.get_min_key();

    assert(tst->key == 1);
    assert(f.get_nodes() == 5);

    while (true) {
        cout << tst->key << " ";
        tst = tst->right;
        if (tst == f.get_min_key()) {
            break;
        }
    }
    cout << endl;

    tst = f.get_min_key();
    while (true) {
        cout << tst->key << " ";
        tst = tst->left;
        if (tst == f.get_min_key()) {
            break;
        }
    }
    cout << endl;

    ntst = f.create_node(100);
    f.insert(ntst);

    // extract (and delete) min value of the heap 
    assert(f.get_nodes() == 6);
    assert(f.extract_min() == 1);
    assert(f.get_min_key()->key == 2);
    assert(f.get_nodes() == 5);

    // decrease key 
    f.decrease_key(ntst, 1);
    assert(f.get_min_key()->key == 1);
    f.decrease_key(ntst, 100);
    assert(f.get_min_key()->key == 1);
    f.decrease_key(ntst, 0);
    assert(f.get_min_key()->key == 0);
    assert(f.get_nodes() == 5);

    f.insert(f.create_node(100));
    f.insert(f.create_node(100));
    f.insert(f.create_node(93));

    assert(f.get_nodes() == 8);

    // empty the heap 
    while (f.get_nodes() > 0) {
        cout << "extracted: " << f.extract_min() << endl;
    }

    assert(f.get_nodes() == 0);

    return 0; 
}