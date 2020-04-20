/*

Felipe Rodriguez Atuesta
CMPUT 403 project 

instances of elements in the heap

*/

class node { 
    public:
    // data
    node * parent;
    node * child;
    node * left;
    node * right;
    int key;
    int degree;
    bool mark;
};