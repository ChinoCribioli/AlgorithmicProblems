// Problem statement:
// https://cses.fi/problemset/task/2072/


#include <bits/stdc++.h>

using namespace std;

// This is a command used in CP to make input-output faster
void fastIO() { ios_base::sync_with_stdio(false), cin.tie(0); }

struct Node;
using NodePtr = Node *;

struct Node {
	int priority;
	char c;
	int size;
	NodePtr left, right;

	Node(char ch) {
		c = ch;
		priority = rand();
		left = right = nullptr;
		size = 1;
	}
};

int get_size(NodePtr root) { 
	return root ? root->size : 0;
}

void evaluate(NodePtr root) {
	if (root) {
		root->size = get_size(root->left) + get_size(root->right) + 1;
	}
}

pair<NodePtr, NodePtr> split(NodePtr root, int amount) {
	if (root == nullptr) return {nullptr, nullptr};

	int take = get_size(root->left) + 1;
	if (take <= amount) {
		auto [left, right] = split(root->right, amount - take);
		root->right = left;
		evaluate(root);
		return {root, right};
	} else {
		auto [left, right] = split(root->left, amount);
		root->left = right;
		evaluate(root);
		return {left, root};
	}
}

NodePtr merge(NodePtr left, NodePtr right) {
	if (left == nullptr) return right;
	if (right == nullptr) return left;

	if (left->priority > right->priority) {
		left->right = merge(left->right, right);
		evaluate(left);
		return left;
	} else {
		right->left = merge(left, right->left);
		evaluate(right);
		return right;
	}
}

void heapify(NodePtr root) {
	if (root == nullptr) return;

	NodePtr maxPriority = root;
	if (root->left != nullptr && root->left->priority > maxPriority->priority) {
		maxPriority = root->left;
	}
	if (root->right != nullptr && root->right->priority > maxPriority->priority) {
		maxPriority = root->right;
	}

	if (maxPriority != root) {
		swap(maxPriority->priority, root->priority);
		heapify(maxPriority);
	}
}

NodePtr build(const string &v, int from, int to) {
	// This function constructs a balanced treap with the chars in the order given by v
	if (from == to) return nullptr;

	int mid = (from + to) / 2;
	NodePtr root = new Node(v[mid]);
	root->left = build(v, from, mid);
	root->right = build(v, mid + 1, to);

	heapify(root);
	evaluate(root);
	return root;
}

void toString(NodePtr root, string &s) {
	// This returs the string formed by the characters of the treap in the order given by the tree
	if (root == nullptr) return;

	toString(root->left, s);
	s += root->c;
	toString(root->right, s);
}

int main() {
	fastIO();
	int n, q;
	cin >> n >> q;

	string s;
	cin >> s;
	NodePtr root = build(s, 0, n);

	for (int i = 0; i < q; i++) {
		int from, to;
		cin >> from >> to;

		NodePtr left, middle, right;
		// left = [1, to]
		// right = [to + 1, n]
		tie(left, right) = split(root, to);

		// left   = [1, from - 1]
		// middle = [from, to]
		// right  = [to + 1, n]
		tie(left, middle) = split(left, from - 1);

		root = merge(merge(left, right), middle);
	}

	string ans;
	toString(root, ans);
	cout << ans << '\n';
}
