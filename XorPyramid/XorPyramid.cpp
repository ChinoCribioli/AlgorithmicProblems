// Problem statement:
// https://cses.fi/problemset/task/2419/

#include <iostream>
#include <vector>
using namespace std;

int main() {
	// This is a command used in CP to make input-output faster
	ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
	cin >> n;
	vector<int> a(n), b(0); // b will be an auxiliar vector used in the jumps.
	for(int i = 0 ; i < n ; i++) cin >> a[i];
	
	// Since we are going to perform power-of-2 jumps, we have to compute the greatest power that is less or equal than n.
	int pow = 0;
	while(n >= (1 << pow)) pow++;
	pow--;
	
	// We will perform jumps until our level consists of only 1 number. The variable n will keep track of this value.
	while(n > 1){ 
		// We will only do jumps of powers of 2 that are present in n's binary representation.
		if(!(n>>pow && 1)){ pow--; continue;}
		
		int jump_size = (1<<pow)-1;
		// b will be storing the new level as we compute it, and at the end we will assign a = b.
		b.resize(n-jump_size);
		int aux = 0;
		for(int i = 0 ; i < jump_size ; i++) aux ^= a[i];
		// At this point, aux contains the xor of the first "jump_size" values of the current level of the pyramid.
		for(int i = 0 ; i < (int)b.size() ; i++) {
			// We update aux to contain the xor of the elements in the interval [i, i+jump_size]
			if(i) aux ^= a[i-1];
			aux ^= a[jump_size+i];
			b[i] = aux;
		}
		// We update the values of the level and the number of level we are at after the jump.
		a.swap(b);
		n -= jump_size;
	}
	cout << a[0] << endl;
}
