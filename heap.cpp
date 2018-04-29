#include "heap.h"


MinHeap::MinHeap(int _capacity)
{
	//init a heap with desired capacyity
	capacity = _capacity;
	arr = new TreeNode[capacity];
	size = 0;
}

MinHeap::MinHeap(TreeNode *_arr, int _size) {
	//copy elements of an array into the heap
	size = _size;
	capacity = _size;
	arr = new TreeNode[capacity];

	for (int i = 0; i < size; ++i) {
		arr[i] = _arr[i];
	}

	//heapify in case the array wasn't a heap
	heapify();
}

void MinHeap::fromArray(TreeNode *_arr, int _size) {
	delete[] arr;
	//copy elements of an array into the heap
	size = _size;
	capacity = _size;
	arr = new TreeNode[capacity];

	for (int i = 0; i < size; ++i) {
		arr[i] = _arr[i];
	}

	//heapify in case the array wasn't a heap
	heapify();
}

//release memory
MinHeap::~MinHeap() {
	
	delete[]arr;
}

int MinHeap::getSize() { return size; }

//insert an element into the heap
void MinHeap::insert(TreeNode A) {
	//it could be necessary to get a bigger size of heap
	if (size == capacity) {
		capacity *= 2;
		TreeNode *nArr = new TreeNode[capacity];
		for (int i = 0; i < size; ++i) {
			nArr[i] = arr[i];
		}

		delete[]arr;
		arr = nArr;
	}

	//set in last position
	arr[size] = A;
	size++;

	//bubble up the element
	bubbleUp(size - 1);
}

//get element with highest priority
TreeNode MinHeap::getMin() {
	return arr[0];
}

//erase element with highest priority
void MinHeap::popMin() {
	//put last element in first position and bubble it down
	size--;
	arr[0] = arr[size];

	bubbleDown(0);
}

//print elements in heap
void MinHeap::print() {
	
	for (int i = 0; i < size; ++i) {
		cout << i << ": ";
		arr[i].print();
	}
}

//get left child of a specific position
int MinHeap::left(int pos) {
	return 2 * pos + 1;
}

//get right child of a specific position
int MinHeap::right(int pos) {
	return 2 * pos + 2;
}

//get father of a specific position
int MinHeap::father(int pos) {
	return (pos - 1) / 2;
}

//bubble up an element
void MinHeap::bubbleUp(int pos) {
	int p = pos;
	int f = father(p);

	//compare priority of an element with his father's and swap them if necessary
	while (p > 0 && arr[p].frequency < arr[f].frequency) {
		TreeNode aux = arr[p];
		arr[p] = arr[f];
		arr[f] = aux;

		p = f;
		f = father(p);
	}
}

//bubble down an element
void MinHeap::bubbleDown(int pos) {
	int r = pos;
	int son = left(r);
	while (son < size)
	{
		//decide which son has higher priority
		if (son < size - 1 &&
			arr[son].frequency >= arr[son + 1].frequency)
			son++;

		//compare priority of an element with his son and swap if necessary
		if (arr[r].frequency > arr[son].frequency) {
			TreeNode aux = arr[r];
			arr[r] = arr[son];
			arr[son] = aux;

			r = son;
			son = left(r);
		}
		else return;

	}
}

//transform the array in a heap
void MinHeap::heapify() {
	for (int r = size / 2; r >= 0; --r) {
		bubbleDown(r);
	}
}