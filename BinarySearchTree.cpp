/* 
 * BinarySearchTree.cpp
 */

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>

#include "BinarySearchTree.h"

using namespace std;

//Function: search tree constructor
//Parameters: none
//Output: none
//Does: constructs a binary search tree
BinarySearchTree::BinarySearchTree()
{
    root = NULL;
}

//Function: binary search tree destructor
//Parameters: none 
//Output: none
//Does: calls post order delete to do a post order traversal and
// delete the tree
BinarySearchTree::~BinarySearchTree()
{
        // walk tree in post-order traversal and delete
        post_order_delete(root);
        root = NULL;   // not really necessary, since the tree is going 
                       // away, but might want to guard against someone
                       // using a pointer after deleting
}

//Function: post_order_delete
//Parameters: pointer to a node
//Output: none
//Does: uses post-order traversal to delete a node
void BinarySearchTree::post_order_delete(Node *node)
{
    if (node == NULL)
        return;
    if (node->left){
        delete node->left;
        node->left = NULL;
        post_order_delete(node->left);
    }
    if (node->right){
        delete node->right;
        node->right = NULL;
        post_order_delete(node->right);
    }
    delete node;
    return;
}

// copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source)
{
        // use pre-order traversal to copy the tree
        root = pre_order_copy(source.root);
}

// assignment overload
BinarySearchTree &BinarySearchTree::operator= (const BinarySearchTree &source)
{
    if (this != &source){
        post_order_delete(root);
        root = pre_order_copy(source.root);
    }
    return *this;
}

//Function: pre_order_copy
//Parameters: pointer to a node
//Output: node
//Does: uses pre-order traversal to copy a node
Node *BinarySearchTree::pre_order_copy(Node *node) const
{
    if (node == NULL){
        return NULL;
    }
    Node *newRoot;
    newRoot = new Node;
    newRoot->data = node->data;
    newRoot->count = node->count;
    newRoot->left = pre_order_copy(node->left);
    newRoot->right = pre_order_copy(node->right);
    return newRoot;
}

//Function: find_min
//Parameters: none
//Output: int minimum of tree values
//Does: recursively finds the minimum of the root
int BinarySearchTree::find_min() const
{
    if (root == NULL)
        return INT_MIN;
    return find_min(root)->data;
}
//Function: find_min
//Parameters: pointer to a node
//Output: node of minimum of tree values
//Does: recursively finds the minimum of the given node
Node *BinarySearchTree::find_min(Node *node) const
{
    if (node->left != NULL)
        return find_min(node->left);
    else if (node->left == NULL)
        return node;
    else return NULL;
}

//Function: find_max
//Parameters: none
//Output: int maximum of tree values
//Does: recursively finds the max of the root
int BinarySearchTree::find_max() const
{
    if (root == NULL)
        return INT_MAX;
    return find_max(root)->data;
}

//Function: find_max
//Parameters: pointer to a node
//Output: node of maximum of tree values
//Does: recursively finds the max of the given node
Node *BinarySearchTree::find_max(Node *node) const
{
    if (node->right != NULL)
        return find_max(node->right);
    else if (node->right == NULL)
        return node;
    else return NULL;
}

//Function: contains
//Parameters: value searching for
//Output: true or false of value found
//Does: recursively checks if root is equal to value
bool BinarySearchTree::contains(int value) const
{
    if (root == NULL)
        return false;
    else return contains(root, value);
}

//Function: contains
//Parameters: value searching for and pointer to a node
//Output: true or false if value found
//Does: recursively checks if given node is equal to value
bool BinarySearchTree::contains(Node *node, int value) const
{
    if (node == NULL)
        return false;
    else{
        if (value == node->data)
            return true;
        else if (value < node->data)
            return contains(node->left, value);
        else if (value > node->data)
            return contains(node->right, value);
        else
            return false;
    }
}

void BinarySearchTree::insert(int value)
{
    insert(root, NULL, value);
}

void BinarySearchTree::insert(Node *node, Node *parent, int value)
{
    if (node == NULL){
        Node *newNode;
        newNode = new Node;
        root = newNode;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->count = 1;
        newNode->data = value;
        return;
    }
    else if (value < node->data){
        if (node->left == NULL){
            Node *newLeft;
            newLeft = new Node;
            node->left = newLeft;
            newLeft->left = NULL;
            newLeft->right = NULL;
            newLeft->count = 1;
            newLeft->data = value;
            return;
        }
        else 
            insert(node->left, node, value);
    }
    else if (value > node->data){
        if (node->right == NULL){
            Node *newRight;
            newRight = new Node;
            node->right = newRight;
            newRight->left = NULL;
            newRight->right = NULL;
            newRight->count = 1;
            newRight->data = value;
            return;
        }
        else
            insert(node->right, node, value);
    }
    else if (node->data == value){
        (node->count) = (node->count) + 1;
        return;
    }

}
 
bool BinarySearchTree::remove(int value)
{
    return remove(root, NULL, value);
}

//Function: remove
//Parameters: pointer to a node, pointer to a node parent, value to remove
//Output: true or false if a node is removed or a count decremented
//Does: checks 4 cases: if node is null, nothing can be removed.
//if node's left and right are null, the node can be deleted and the
//parent can be repointed to null depending on if the value is smaller
//or larger. 
//if node left or node right is not null, the function is called
//recursively down the tree until it reaches a leaf.
//otherwise, the node has two children, adn the minimum of the left
//subtree of the node is set to null.
bool BinarySearchTree::remove(Node *node, Node *parent, int value)
{
    if (node == NULL)
        return false;
    if (node->data == value){
        if(node->count > 1){ 
            (node->count) = (node->count) - 1;
            return true;
        }
        else if (node->left == NULL && node->right == NULL){
            if (value < parent->data){
                delete node;
                parent->left = NULL;
            }
            else if (value > parent->data){
                delete node;
                parent->right = NULL;
            }
            return true;
        }
        else if (node->left != NULL && node->right == NULL){
            parent->left = node->left;
            delete node;
            return true;
        }
        else if (node->right != NULL && node->left == NULL){
            parent->right = node->right;
            delete node;
            return true;
        }
        // if node has two children
        else{
            Node *min_subtree = find_min(node->right);
            node->count = min_subtree->count;
            node->data = min_subtree->data;
            Node *temp = find_parent(node->right, min_subtree);
            temp->left = min_subtree->right;
            delete min_subtree;
            return true;
        }
    }
    if (value < node->data){
        return remove(node->left, node, value);
    }
    else if (value > node->data)
        return remove(node->right, node, value);
    else return false;
}

//Function: tree_height
//Parameters: none
//Output: int of tree height
//Does: recursively finds the height of the tree
int BinarySearchTree::tree_height() const
{
    if (root == NULL)
        return 0;    
    return tree_height(root);
 }

//Function: tree_height
//Parameters: pointer to a node
//Output: int of tree height
//Does: recursively finds the height of the tree
int BinarySearchTree::tree_height(Node *node) const
{
    if (node == NULL)
        return 0;
    else{
        int left_ht = tree_height(node->left);
        int right_ht = tree_height(node->right);
        return max(left_ht, right_ht) + 1;
    }
}

// returns the total number of nodes
int BinarySearchTree::node_count() const
{
    return node_count(root);
}
//returns total number of nodes with a pointer to a node passed in
int BinarySearchTree::node_count(Node *node) const
{
    if (node == NULL)
        return 0;
    else
        return 1 + node_count(node->left) + node_count(node->right);
}

// return the sum of all the node values (including duplicates)
int BinarySearchTree::count_total() const
{
    if (root == NULL)
        return 0;
    else
        return count_total(root);
}
//returns sum of all node values with a pointer to a node
int BinarySearchTree::count_total(Node *node) const
{
    if (node != NULL){
        return ((node->data) * (node->count)) + count_total(node->left) + 
            count_total(node->right);
    }
    else
        return 0;
}

// use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() const
{
        printPretty(root, 1, 0, std::cout);
}

Node *BinarySearchTree::find_parent(Node *node, Node *child) const
{
        if (node == NULL) return NULL;

        // if either the left or right is equal to the child,
        // we have found the parent
        if (node->left == child or node->right == child) {
                return node;
        }

        // Use the binary search tree invariant to walk the tree
        if (child->data > node->data) {
                return find_parent(node->right, child);
        } else {
                return find_parent(node->left, child);
        }
}
