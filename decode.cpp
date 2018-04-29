// Decodes text encoded using the Huffman Code Tree
// Usage:  ./decode  preorder  inorder  code.txt

#include <iostream>
#include <fstream>
using namespace std;
struct treenode {
	unsigned char data;
	treenode *left, *right;
};

int strchr(unsigned char s[], unsigned char c) {
	int i = 0;
	while (s[i] != c) i++;
	return i;
}

treenode * treebuild(unsigned char pre[], unsigned char in[], int & pos, int size) {
	if (size == pos) return NULL;
	treenode *t = new treenode;
	t->data = pre[pos]; t->left = NULL; t->right = NULL;
	int loc = strchr(in, pre[pos++]);
	in[loc] = 0;
	if (loc > 0 && in[loc - 1] != 0)
		t->left = treebuild(pre, in, pos, size);
	if (loc < size - 1 && in[loc + 1] != 0)
		t->right = treebuild(pre, in, pos, size);
	return t;
}

void parse(string c, treenode *t) {
	treenode *p = t;
	for (int pos = 0; pos < c.length(); pos++) {
		//cout << c[pos] << " " << pos << endl;
		p = c[pos] == '0' ? p->left : p->right;
		if (p->left == NULL) {
			cout << p->data;
			p = t;
		}
	}
}

int main(int argc, char* argv[]) {
	ifstream prefile(argv[1], ios::in | ios::binary | ios::ate), infile(argv[2], ios::in | ios::binary), codefile(argv[3]);
	size_t size = 0; // here
	size = prefile.tellg(); // get the length of the file
	prefile.seekg(0, ios::beg); // set the pointer to the beginning
	unsigned char *pre = new unsigned char[size], *in = new unsigned char[size];
	for (int i = 0; i<size; i++) {
		pre[i] = prefile.get();
		in[i] = infile.get();
	}

	size_t size2 = 0; // here
	codefile.seekg(0, ios::end);
	size2 = codefile.tellg(); // get the length of the file
	codefile.seekg(0, ios::beg); // set the pointer to the beginning
	size2 = size2;
	char *code = new char[size2+2];
	codefile.getline(code, size2+1);
	//cout << code << endl;
	int pos = 0;
	treenode *tree = treebuild(pre, in, pos, size2);
	parse(code, tree);
	
	cout << endl;

	delete code;
}
