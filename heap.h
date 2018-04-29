#ifndef HEAP_H
#define HEAP_H

#include "tree.h"

#include <iostream>
#include <fstream>
using namespace std;

class MinHeap {
private:
	int size;
	int capacity;
	TreeNode *arr;

public:
	MinHeap(int _capacity);

	MinHeap(TreeNode *_arr, int _size);

	~MinHeap();

	void fromArray(TreeNode *_arr, int _size);

	int getSize();

	void insert(TreeNode A);

	TreeNode getMin();

	void popMin();

	void print();

private:
	int left(int pos);

	int right(int pos);

	int father(int pos);

	void bubbleUp(int pos);

	void bubbleDown(int pos);

	void heapify();
};


#endif // !HEAP_H

