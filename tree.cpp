#include "tree.h"

void TreeNode::print() {
	//cout << "{" << value << ", " << frequency << ", " << left << ", " << right << "}" << endl;
	cout << "{" << value << ", " << frequency << "}" << endl;
}


void TreeNode::inOrder(ofstream &infile) {
	if (left != NULL) left->inOrder(infile);
	//cout << (int)root->value <<" "<< root->frequency << endl;
	infile.put((unsigned char)value);
	//cout << (unsigned char)root->value << endl;
	if (right != NULL) right->inOrder(infile);
}

void TreeNode::preOrder(ofstream &prefile) {
	prefile.put((unsigned char)value);
	if (left != NULL) left->preOrder(prefile);
	if (right != NULL) right->preOrder(prefile);
	//cout << (unsigned char)root->value << endl;
	//cout << (int)root->value << " " << root->frequency << endl;
}

void TreeNode::deleteTree() {
	if (left != NULL) {
		left->deleteTree();
		delete left;
	}

	if (right != NULL) {
		right->deleteTree();
		delete right;
	}
}