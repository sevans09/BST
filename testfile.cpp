#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

void print_tree_details(BinarySearchTree &bst)
{
        bst.print_tree();
        cout << "\n";
        cout << "min: "         << bst.find_min()    << "\n";
        cout << "max: "         << bst.find_max()    << "\n";
        cout << "nodes: "       << bst.node_count()  << "\n";
        cout << "count total: " << bst.count_total() << "\n";
        cout << "tree height: " << bst.tree_height() << "\n";
        cout << "\n";
}

int main() 
{ 


	Node n1;
	n1.data = 0;
	n1.count = 0;
	n1.left = NULL;
	n1.right = NULL;
	
	cerr << "Initializing tree" << endl;
	cerr << "node val: " << n1.data << endl;
	BinarySearchTree tree;
    int values[]  = {4, 2, 11, 15, 9, 1, -6, 5, 3, 15, 5, 13, 14};
    int numValues = sizeof(values) / sizeof(int);
	for (int i = 0; i < numValues; i++) {
    	tree.insert(values[i]);
    }
            cout << "Original tree "
             << "(asterisks denote a count of more than 1):\n";
    print_tree_details(tree);
    cout << tree.find_min();
	cerr <<  "tree printed" << endl;

	cerr << "inserting value" << endl;
	tree.insert(1);
	tree.print_tree();
	tree.insert(6);
	tree.insert(18);
	tree.insert(10);
	tree.insert(9);
	tree.print_tree();
	tree.print_tree();
	cout << tree.node_count() << endl;
	cout << "count total" << endl;
	cout << tree.count_total() << endl;
	cout << tree.find_min() << endl;
	cout << tree.find_max() << endl;
	cout << tree.contains(1);
	cout << tree.contains(5);
	cout << tree.tree_height() << endl;;
	tree.print_tree();

		return 0;
}