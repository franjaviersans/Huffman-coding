#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <fstream>
using namespace std;

class TreeNode {
public:
	unsigned char value;
	int frequency;
	TreeNode *left, *right;
	TreeNode() : frequency(0.0f), value(0), left(NULL), right(NULL) {}
	TreeNode(unsigned char _value, int _frequency) :
		frequency(_frequency), value(_value), left(NULL), right(NULL) {}

	TreeNode(const TreeNode &a) :
		frequency(a.frequency), value(a.value), left(a.left), right(a.right) {}

	void print();

	void inOrder(ofstream &infile);

	void preOrder(ofstream &prefile);

	void deleteTree();
};

#endif // !TREE_H

