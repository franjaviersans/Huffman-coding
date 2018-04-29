#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
int main(int argc, char *argv[]) {
	unsigned char ch;
	ifstream in(argv[1], ios::in | ios::binary | ios::ate);
	size_t size = 0; // here
	size = in.tellg(); // get the length of the file
	in.seekg(0, ios::beg); // set the pointer to the beginning
	for (int i = 0; i<size; i++) {
		ch = in.get();
		cout << setw(3) << setfill('0') << (int)ch << " ";
	}
	cout<<endl;
}
