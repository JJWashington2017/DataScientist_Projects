/*This is MicroAssignment Project for my classes. Dr. Aaron Crandall did part of the codes as a start for students.
 * Jie Zhao -2017 -Added/updated.
 * Aaron Crandall - 2016 - Added / updated:
 *  * Inorder, Preorder, Postorder printouts
 *  * Stubbed in level order printout
 * Aaron Crandall - 2017 - Heavy overhaul of tests & behaviors
 *  * Added BigFive (like we should!)
 *  * Added several public interfaces for tree features
 *
 */

#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <cstring>		// strcmp
#include <vector>
#include <queue>
#include <initializer_list>

using namespace std;

/*
 *  Node datastructure for single tree node
 */ 
template <class T>
struct Node {
    T value;
    Node *left;
    Node *right;
    
    Node ()
    {
        
    }

    Node(T val) {
        this->value = val;
        this->left = NULL;
        this->right = NULL;
    }

    Node(T val, Node<T> * left, Node<T> * right) {
        this->value = val;
        this->left = left;
        this->right = right;
    }
};

/*
 * Binary Search Tree (BST) class implementation
 */
template <class T>
class BST {

    private:
    Node<T> *root;

    /* clone a passed in tree, returns pointer to new tree */
    Node<T> * cloneTree(Node<T> *t) {
        if( t == NULL )
            return NULL;
        else
            return new Node<T>( t->value, 
                                cloneTree( t->left ),
                                cloneTree( t->right ) );
    }

    /* Recursively delete the tree nodes */
    void makeEmptyHelper(Node<T> *t) {
        if( t != NULL ) {
            makeEmptyHelper( t->left );
            makeEmptyHelper( t->right );
            delete t;
        }
    }

    /* Add new T val to the tree */
    void addHelper(Node<T> *root, T val) {
        if (root->value > val) {
            if (!root->left) {
                root->left = new Node<T>(val);
            } else {
                addHelper(root->left, val);
            }
        } else {
            if (!root->right) {
                root->right = new Node<T>(val);
            } else {
                addHelper(root->right, val);
            }
        }
    }

    /* Print tree out in inorder (A + B) */
    void printInOrderHelper(Node<T> *root) {
        if (!root) return;
        printInOrderHelper(root->left);
        cout << root->value << ' ';
        printInOrderHelper(root->right);
    }

    /* Print tree out in post order (A B +) */
    void printPostOrderHelper(Node<T> *root) {
        if (!root) return;
        printPostOrderHelper(root->left);
        printPostOrderHelper(root->right);
        cout << root->value << ' ';
    }

    /* Print tree out in pre order (+ A B) */
    void printPreOrderHelper(Node<T> *root) {
        if (!root) return;
        cout << root->value << ' ';
        printPreOrderHelper(root->left);
        printPreOrderHelper(root->right);
    }

    /* Print tree out in level order */
    /* MA TODO: Implement */
    void printLevelOrderHelper(Node<T> *root) {
        if (!root) return;
        /*
        MA TODO:
        */
        cout << endl;
        cout << "printLevelOrderHelper UNIMPLEMENTED AT THIS TIME -- REPLACE!" << endl;
        cout << " ** Required to use the STL queue class (that's a huge hint)!" << endl;
        
        std:: queue< Node<T>* > q;  //make a queue and allocate memory;
        
         q.push(root);
        // root = q.pop();
        
        //cout << "haha got it "<< q.front() << endl; // add the root node to the queque;
        
        while (!q.empty())
        {
            Node<T> * temp = q.front();
            cout << temp->value << endl; // print out the data
            q.pop();
            if (temp->left !=nullptr)
                q.push(temp->left );
            if (temp->right !=nullptr)
                q.push(temp->right);
        
        }
        
        
        cout << " ** Doing this with a loop will be easier than recursion." << endl;
    }

    /* Generate vector of tree values to return */
    /* MA TODO: Implement */
    vector<T> & returnLevelOrderHelper(Node<T> *root) {
        vector<T> * ret = new vector<T>{};
        if (!root) return( *ret );
        /*
        MA TODO:
        */
        //cout << endl;
       // cout << " returnLevelOrderHelper UNIMPLEMENTED AT THIS TIME -- REPLACE!" << endl;
       // cout << " ** Required to use the STL queue class (that's a huge hint)!" << endl;
        std:: queue< Node<T>* > q;  //make a queue and allocate memory;
        
        q.push(root);
        // root = q.pop();
        
        //cout << "haha got it "<< q.front() << endl; // add the root node to the queque;
        
        while (!q.empty())
        {
            Node<T> * temp = q.front();
            ret->push_back(temp->value);
           // cout << temp->value << endl; // print out the data
            q.pop();
            if (temp->left !=nullptr)
                q.push(temp->left );
            if (temp->right !=nullptr)
                q.push(temp->right);
            
        }
        //cout << " ** Doing this with a loop will be easier than recursion." << endl;
        return( *ret );
    }

    
    
    
    /* Return number of nodes in tree */
    int nodesCountHelper(Node<T> *root) {
        if (!root) return 0;
        else return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
    }

    /* Return height of tree (root == NULL -> 0) */
    int heightHelper(Node<T> *root) {
        if (!root) return 0;
        else return 1 + max(heightHelper(root->left), heightHelper(root->right));
    }

    /* Print out longest path from root to a leaf */
    void printMaxPathHelper(Node<T> *root) {
        if (!root) return;
        cout<<root->value<<' ';
        if (heightHelper(root->left) > heightHelper(root->right)) {
            printMaxPathHelper(root->left);
        } else {
            printMaxPathHelper(root->right);
        }
    }

    /* Delete a given T value from tree */
    bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value) {
        if (!current) return false;
        if (current->value == value) {
            if (current->left == NULL || current->right == NULL) {
                Node<T>* temp = current->left;
                if (current->right) temp = current->right;
                if (parent) {
                    if (parent->left == current) {
                        parent->left = temp;
                    } else {
                        parent->right = temp;
                    }
                } else {
                    this->root = temp;
                }
            } else {
                Node<T>* validSubs = current->right;
                while (validSubs->left) {
                    validSubs = validSubs->left;
                }
                T temp = current->value;
                current->value = validSubs->value;
                validSubs->value = temp;
                return deleteValueHelper(current, current->right, temp);
            }
            delete current;
            return true;
        }
        return deleteValueHelper(current, current->left, value) ||
               deleteValueHelper(current, current->right, value);
    }

    bool containsHelper(Node<T> * root, T val) {
        if( root == NULL )
            return( false );
        else if( root->value == val )
            return( true );
        else if( root->value > val ) // Search left
            return( containsHelper(root->left, val) );
        else
            return( containsHelper(root->right, val) );
    }


    public:

    BST( ) : root( NULL ) { }                   // Basic initialization constructor

    BST( initializer_list<T> vals ) : root( NULL ) {   // Vector-based initializer
        for( auto val : vals )
            this->add(val);
    }

    ~BST( ) {                             // Destructor - free all nodes
        makeEmpty( );
    }

    /* Copy constructor */
    /* MA TODO: Implement */
    BST( const BST &other ) : root( NULL ) {
        cout << " [d] Copy constructor called. " << endl;
        if (this == &other)
            return;
        root = cloneTree(other.root);
        cout << " TODO: Implement copy constructor. " << endl;
    }

    /* Move constructor */
    /* MA TODO: Implement */
    BST ( BST && other ) : root( NULL ) {
        cout << " [d] Move constructor called " << endl;
  
        this->root= other.root;
        
        other.root=nullptr;
        //makeNullHelper(other.root);
    
        //cout << (other.root)<<"haha"<< endl;
        //cout << root<<"haha"<<endl;
        //cout << (other.root)->left<< endl;
        //cout << root->left<< endl;
    
        cout << " TODO: Implement move constructor. " << endl;
    }
    
    
    
    
    void makeNullHelper(Node<T> *t) {
        if( t != nullptr ) {
            //t= nullptr;
             //cout << t << endl;
            makeNullHelper( t->left );
            //t= nullptr;
            // cout << t << endl;
            makeNullHelper( t->right );
            //t->value =0;
            t= nullptr;
            delete t;
            cout << t << endl;
        }
    }


    /* Copy assignment operator */
    /* MA TODO: Implement */
    BST& operator=(BST & other) {
        cout << " [d] Copy assignment operator called. " << endl;
        root = cloneTree(other.root);
        cout << " TODO: Implement copy assignment operator. " << endl;
    }

    /* Move assignment operator */
    /* MA TODO: Implement */
    BST& operator=(BST && other) {
        cout << " [d] Move assignment operator called. " << endl;
        this->root= std::move(other.root);
        other.root=nullptr;
        //makeNullHelper(other.root);
        
        cout << " TODO: Implement move assignment operator. " << endl;
    }

    /* Public API */
    void makeEmpty( ) {
        if (root) 
            this->makeEmptyHelper(root);
    }

    void add(T val) {
        if (root) {
            this->addHelper(root, val);
        } else {
            root = new Node<T>(val);
        }
    }

    bool empty() {
        return( root != NULL );
    }

    void print() {
        printInOrderHelper(this->root); 
    }

    void printInOrder() {
        printInOrderHelper(this->root);
    }

    void printPostOrder() {
        printPostOrderHelper(this->root);
    }

    void printPreOrder() {
        printPreOrderHelper(this->root);
    }

    void printLevelOrder() {
        printLevelOrderHelper(this->root);
    }

    vector<T> & returnLevelOrder() {
        return returnLevelOrderHelper(this->root);
    }

    int nodesCount() {
        return nodesCountHelper(root);
    }

    int height() {
        return heightHelper(this->root);
    }

    void printMaxPath() {
        printMaxPathHelper(this->root);
    }

    bool deleteValue(T value) {
        return this->deleteValueHelper(NULL, this->root, value);
    }

    bool contains( T value ) {
        containsHelper(this->root, value);
    }

    Node<T> * getRoot() { return(root); }  // Gives out our root pointer for testing
    

};


#endif
