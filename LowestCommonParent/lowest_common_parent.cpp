#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

struct File {
	
	string name;
	vector<File*> children, ancestors;
	int depth;
	const int MAX_POW = 30; // This value has to be greater than log_2(n), where n is the number of files in our filesystem
	
	File(string fileName){
		this->name = fileName;
		this->children = vector<File*>(0);
		this->ancestors = vector<File*>(MAX_POW+1,nullptr); // ancestors[i] will store a pointer to the 2^i-th parent of the file
		this->depth = 0; // depth will store the level of the file starting down from the root, which will have depth 0
	}
	
	~File() {
		for (File* pointer : children) {
			delete pointer;
		}
		//~ cout << "Deleted " << this->name << endl;
	}
	
	void addChild(File* child){
		child->depth = this->depth+1;
		child->ancestors[0] = this;
		for (int power = 1 ; power <= MAX_POW ; power++) {
			// The 2^i-th parent of a node will be the 2^(i-1)-th parent of the 2^(i-1)-th parent of the node.
			File* previous = child->ancestors[power-1];
			child->ancestors[power] = previous ? previous->ancestors[power-1] : nullptr;
		}
		this->children.push_back(child);
	}
	
};

File* findParent(File* a, File* b) {
	if (a == nullptr || b == nullptr) return nullptr;
	
	if (a->depth > b->depth) {
		swap(a,b);
	}
	
	int depthDif = b->depth - a->depth;
	int smallestPow = 1, index = 0;
	// We will mantain the following invariants:
	// 1) smallestPow = 2^index
	// 2) b->depth + depthDif = a->depth

	// First, we equalize the depths of the nodes.
	while (2*smallestPow <= depthDif) {
		smallestPow *= 2;
		index++;
	}
	while (depthDif) {
		while(smallestPow > depthDif) {
			smallestPow /= 2;
			index--;
		}
		b = b->ancestors[index]; // It's guaranteed that b has ancestors because its depth is still greater than a->depth
		depthDif -= smallestPow;
	}
	
	assert(a->depth == b->depth);
	
	// Now that they are at the same level, we go up exponentially unless we find a common parent.
	index = a->MAX_POW;
	while (a != b) {
		while (a->ancestors[index] == b->ancestors[index] && index > 0) {
			index--;
		}
		a = a->ancestors[index];
		b = b->ancestors[index];
	}
	 
	return a;
}

int main() {
	// To test the algorithm, we first create a tower of 17 files.
	File* f1 = new File("file_1");
	File* f2 = new File("file_2");
	f1->addChild(f2);
	File* f3 = new File("file_3");
	f2->addChild(f3);
	assert(findParent(f1,f1)->name == "file_1");
	assert(findParent(f3,f3)->name == "file_3");
	
	File* previous = f3;
	for (int i = 4; i < 18; i++) {
		File* genericFile = new File("file_" + to_string(i));
		previous->addChild(genericFile);
		previous = genericFile;
	}
	
	assert(findParent(f2,f1)->name == "file_1");
	assert(findParent(f3,f1)->name == "file_1");
	assert(findParent(f1,previous)->name == "file_1"); // Previous equals "file_17"
	assert(findParent(previous,f2)->name == "file_2");
	assert(findParent(previous,f3)->name == "file_3");
	
	// Now, let's add files at different parts of the tower
	File* firstSonOf3 = new File("son_1_of_3");
	f3->addChild(firstSonOf3); 
	assert(findParent(previous,firstSonOf3)->name == "file_3");
	File* secondSonOf3 = new File("son_2_of_3");
	f3->addChild(secondSonOf3); 
	assert(findParent(firstSonOf3,secondSonOf3)->name == "file_3");
	File* sonOf2 = new File("son_of_2");
	f2->addChild(sonOf2);
	assert(findParent(previous, sonOf2)->name == "file_2");
	assert(findParent(sonOf2, secondSonOf3)->name == "file_2");
	assert(findParent(sonOf2, firstSonOf3)->name == "file_2");
	
	// If we have two files that don't have a common parent, we should get the null pointer
	File* isolatedFile = new File("isolated");
	assert(findParent(f1,isolatedFile) == nullptr);
	assert(findParent(f3,isolatedFile) == nullptr);
	assert(findParent(secondSonOf3,isolatedFile) == nullptr);
	
	delete f1;
	delete isolatedFile;
	
	return 0;
}
