/*

Felipe Rodriguez Atuesta
CMPUT 403 project 

summary:
    implementation of fibonacci heap 
    performs insert and decrease key functions in amortized O(1)
    other operations perform the same as binary heap

sources:
    Introduction to Algorithms, Third Ed. Cormen Et Al.

    methods implemented using the following pseudocode:
    - inserting a node (page 510)
    - extract min      (page 513)
    - consolidate      (page 516)
    - heap link        (page 516)
    - decrease key     (page 519)
    - cut              (page 519)
    - cascading cut    (page 519)

*/

#include <iostream>
#include <vector>
#include "node.h"

using namespace std;

// fibonacci heap implementation
// have the following public methods:
// create and insert node 
// decrease node value
// extract (and delete) min node value
// get min node value
// get number of nodes in heap
class fibonacci_heap {
    public:

    fibonacci_heap() {
        min_key = NULL;
        nodes   = 0;
    }

    ~fibonacci_heap() {
        // clean all memory from nodes
        deallocate_memory(min_key);
    }

    // public methods

    node * create_node(int val) {
        node * x = new node;

        x->degree = 0;
        x->parent = NULL;
        x->child  = NULL;
        x->mark   = false;
        x->key    = val;

        x->left  = x;
        x->right = x;

        return x;
    }

    // page 510
    void insert(node * x) {
        if (min_key == NULL) {
            // root list containing x
            x->left  = x;
            x->right = x;
            min_key  = x;
        } else {
            // insert x into root list
            (min_key->left)->right = x;
            x->right = min_key;
            x->left = min_key->left;
            min_key->left = x;
            if (x->key < min_key->key) {
                min_key = x;
            }
        }

        ++nodes;
    }

    // page 519
    void decrease_key(node * x, int k) {
        if (k > x->key) {
            return;
        }

        x->key = k;
        node * y = x->parent;

        if (y != NULL && x->key < y->key) {
            cut(x, y);
            cascading_cut(y);
        }

        if (x->key < min_key->key) {
            min_key = x;
        }
    }

    // page 513
    int extract_min() {
        int key_return = -1;
        node * z = min_key;

        if (z != NULL) {
            node * ch = z->child;
            // traverse all children of z
            if (ch != NULL) {
                vector<node*> to_add;
                while (true) {
                    // add child to the root list 
                    to_add.push_back(ch);
                    ch = ch->right;
                    if (ch == z->child) {
                        break;
                    }
                }
                // add all children to root list
                for (auto &chld : to_add) {
                    chld->parent = NULL;
                    add_root(chld);
                }
            }

            // remove z from root list
            (z->left)->right = z->right;
            (z->right)->left = z->left;

            if (z == z->right) {
                // if only node in the heap
                min_key = NULL;
            } else {
                // temporarily select any other node as min_key
                min_key = z->right;
                consolidate();
            }

            key_return = z->key;
            delete z;
            --nodes;
        }
        return key_return;
    }

    // returns min key in heap 
    node * get_min_key() {
        return min_key;
    }

    int get_nodes() {
        return nodes;
    }

    void print_root() {
        node * tst = min_key;

        while (true) {
            cout << tst->key << " ";
            tst = tst->right;
            if (tst == min_key) {
                cout << endl;
                return;
            }
        }
    }

    private:
    // auxiliary methods

    // page 516
    void consolidate() {
        // max degree D(n) <= down(lgn) / page 509
        int max_degree = 100;

        // A[0 .. D(n)]
        vector<node*> a(max_degree, NULL);

        // iterate over all nodes on root
        node * last_node = min_key->left;
        node * x = min_key;
        while (true) {
            node * w = x->right;
            int d = x->degree;
            while (a[d] != NULL) {
                // found a node with same degree as x
                node * y = a[d];
                if (x->key > y->key) {
                    if (x == last_node) {
                        last_node = y;
                    }
                    // exchange x and y
                    node * temp = x;
                    x = y;
                    y = temp;
                }
                link(y, x);
                a[d] = NULL;
                ++d;
            }
            a[d] = x;
            if (x == last_node) {
                break;
            } else {
                // continue iteration
                x = w;
            }
        }

        min_key = NULL;

        for (int i = 0; i < max_degree; ++i) {
            if (a[i] != NULL) {
                if (min_key == NULL) {
                    // create a root list containing only a[i]
                    min_key = a[i];
                    min_key->left  = min_key;
                    min_key->right = min_key;
                } else {
                    add_root(a[i]);
                    if (a[i]->key < min_key->key) {
                        min_key = a[i];
                    }       
                }
            }
        }
    }

    // add an existing note to the root list
    void add_root(node * x) {
        (min_key->left)->right = x;
        x->right = min_key;
        x->left = min_key->left;
        min_key->left = x;
        // min_key should not change here
    }

    // page 516
    void link(node * y, node * x) {
        // remove y from root list 
        (y->left)->right = y->right;
        (y->right)->left = y->left;

        // make y a children of x 
        add_child(x, y);
        y->mark = false;
    }

    void add_child(node * p, node * new_child) {
        new_child->left = new_child;
        new_child->right = new_child;
        new_child->parent = p;

        if (p->child == NULL) {
            // if only child 
            p->child = new_child;
        } else {
            // add new_child in the children list
            ((p->child)->left)->right = new_child;
            new_child->right = p->child;
            new_child->left = (p->child)->left;
            (p->child)->left = new_child;
        }

        p->degree = p->degree + 1;
    }

    // page 519
    void cut(node * x, node * y) {
        // remove x from children of y
        remove_child(x, y);

        // add x to the root 
        add_root(x);
        x->parent = NULL;
        x->mark   = false;
    }

    // remove x from children of y
    void remove_child(node * x, node * y) {
        if (x->right == x) { 
            // only child
            y->child = NULL; 
        } else {
            (x->left)->right = x->right;
            (x->right)->left = x->left;
        }

        y->degree -= 1;
    }

    // page 519
    void cascading_cut(node * y) {
        node * z = y->parent;
        if (z != NULL) {
            if (!y->mark) {
                y->mark = true;
            } else {
                cut(y, z);
                cascading_cut(z);
            }
        }
    }

    void deallocate_memory(node * n) {
        if (n != NULL) {
            // iterate over all children 
            node * ch = n->child;
            if (ch != NULL) {
                while (true) {
                    node * temp = ch;
                    ch = ch->right;
                    deallocate_memory(temp);
                    if (ch == n->child) {
                        break;
                    }
                }
            }

            delete n;
        }
    }

    // data
    node * min_key; // node with min value in the heap
    int nodes;      // number of nodes 
};