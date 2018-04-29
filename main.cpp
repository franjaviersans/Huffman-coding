#include <iostream>
#include <fstream>
#include "heap.h"
using namespace std;


MinHeap heap(10);
TreeNode *TreeRoot = NULL;
string table[256];
int freq[256];
bool app[256];


//function to get the table of strings from a tree
void getTable(TreeNode *root, string a) {
	if (root == NULL) return;
	if (root->left == NULL && root->right == NULL) {
		table[(int)root->value] = a;
	}else{
		if (root->left != NULL) {
			getTable(root->left, a + '0');
		}

		if (root->right != NULL) {
			getTable(root->right, a + '1');
		}
	}
}

//generate the tree from the frequencies
void buildTree() {
	if (heap.getSize() == 0) {
		cout << "Text didn't contain any character!!!" << endl;
	}

	unsigned char label = 128;
	//create tree
	while (heap.getSize() > 1) {
		//get the two nodes with minimun frequency
		TreeNode *a = new TreeNode(heap.getMin());
		heap.popMin();
		TreeNode *b = new TreeNode(heap.getMin());
		heap.popMin();
		//create a new node with new label
		TreeNode interNode(label, a->frequency + b->frequency);
		label = label + 1;
		
	
		//set the other two nodes as sons of this new node
		if (a->value < 128 && b->value < 128 && a->frequency != b->frequency) {
			if (a->value > b->value) {
				interNode.left = a;
				interNode.right = b;
			}
			else {
				interNode.left = b;
				interNode.right = a;
			}
		}
		else {
			if (a->frequency > b->frequency) {
				interNode.left = a;
				interNode.right = b;
			}
			else {
				interNode.left = b;
				interNode.right = a;
			}
		}

		//insert it into the heap
		heap.insert(interNode);
	}

	TreeRoot = new TreeNode(heap.getMin());
	heap.popMin();

	//generate table of strings from the tree
	getTable(TreeRoot, "");
}


//function to read the file
void readFile(ifstream &in, int size) {
	unsigned char ch;
	int count = 0;

	//init arrays
	for (int i = 0; i < 256; ++i) {
		freq[i] = 0;
		app[i] = false;
	}

	//read each character and acummulate the number of ocurrences
	for (int i = 0; i<size; i++) {
		ch = in.get();
		if (ch > 128) {
			cout << ch << endl;
			cin.get();
		}
		if (ch >= 256) cout << "What!!! " << endl;
		freq[(int)ch]++;
		if (!app[(int)ch]) {
			app[(int)ch] = true;
			++count;
		}
	}

	TreeNode * arrcount = new TreeNode[count];
	int pos = 0;
	for (int i = 0; i < 256; ++i) {
		if (app[i]) {
			//get frequency		
			freq[i];
			//create one node in the heap for each frequency
			arrcount[pos].frequency = freq[i];
			arrcount[pos].value = (unsigned char)i;
			++pos;
			
		}
	}
	heap.fromArray(arrcount, count);
	delete[] arrcount;
}

void encodeFile(ifstream &in, int size) {
	unsigned char ch;

	//encode the text
	ofstream outFile("code.txt", ios::out);
	in.seekg(0, ios::beg); // set the pointer to the beginning

	for (int i = 0; i<size; i++) {

		ch = in.get();
		//cout << table[(int)ch].c_str() << endl;
		outFile << table[(int)ch].c_str();
		cout << table[(int)ch].c_str();
	}
	cout<<endl;
}

void encodeFileBin(ifstream &in, int size) {
	unsigned char ch;

	//code the text
	ofstream outBinFile("code.bin", ios::out | ios::binary);
	in.seekg(0, ios::beg); // set the pointer to the beginning

	short count = size;
	unsigned int cc = 0;
	unsigned char num = 0;
	//write the amount of characters
	outBinFile.write((char*)&count, sizeof(count));

	for (int i = 0; i<size; i++) {
		ch = in.get();
		for (unsigned int j = 0; j < table[(int)ch].size(); ++j) {
			num <<= 1;
			if (table[(int)ch][j] == '1') num |= 1;
			++cc;
			//generate bytes concatenating enconded character's codes
			if (cc == 8) {
				//every 8 bites, write it to the file
				outBinFile << num;
				num = 0;
				cc = 0;
			}
		}
	}

	//padd with 0 if it is necessary
	if (cc != 0) {
		while (cc < 8) {
			num <<= 1;
			++cc;
		}
		outBinFile << num;
	}
}

int main(int argc, char *argv[]) {
	

	ifstream in(argv[1], ios::in | ios::binary | ios::ate);
	
	size_t size = 0; // here
	size = in.tellg(); // get the length of the file
	in.seekg(0, ios::beg); // set the pointer to the beginning

	//read input file
	readFile(in, size);

	//build tree from frequencies
	buildTree();

	//create preorder and inorder files
	ofstream infile("inorder", ios::out | ios::binary);
	TreeRoot->inOrder(infile);
	infile.close();
	ofstream prefile("preorder", ios::out | ios::binary);
	TreeRoot->preOrder(prefile);
	prefile.close();

	//generate encoded file
	encodeFile(in, size);


	//generate encoded binary file
	encodeFileBin(in, size);
	
	//free memory
	TreeRoot->deleteTree();
	delete TreeRoot;
}
