#include <iostream>

using namespace std;

#define MAX_NODES 32
#define MAX_INPUT 14
#define NOT_DEF -1

int N;

typedef struct __node_info {
	int parent;
	int node_i;
} node_info;

node_info tree_info[MAX_INPUT];

int arr_tree[MAX_NODES];

void init_node_tree();
void visit(int node_i);
void preorder(int node_i);
void inorder(int node_i);
void postorder(int node_i);

int main() {
	int tc;
	int parent;
	int child;
	int idx;

	init_node_tree();
	cin >> N;

	arr_tree[1] = 1;
	tree_info[1].node_i = 1;

	for (tc = 0; tc < N; tc++) {
		cin >> parent >> child;
		tree_info[child].parent = parent;
		idx = tree_info[parent].node_i * 2;
		if (arr_tree[idx] == NOT_DEF) {
			tree_info[child].node_i = idx;
			arr_tree[idx] = child;
		}
		else {
			tree_info[child].node_i = idx + 1;
			arr_tree[idx + 1] = child;
		}
	}
	cout << "traverse tree by preorder:vLR" << endl;
	preorder(1);
	cout << endl << "traverse tree by inorder:LvR" << endl;
	inorder(1);
	cout << endl << "traverse tree by postorder:LRv" << endl;
	postorder(1);
	cout << endl;
	return 0;
}

void init_node_tree() {
	int idx;
	for (idx = 0; idx < MAX_NODES; idx++) {
		arr_tree[idx] = NOT_DEF;
	}
	for (idx = 0; idx < MAX_INPUT; idx++) {
		tree_info[idx].node_i = NOT_DEF;
		tree_info[idx].parent = NOT_DEF;
	}
}

void visit(int node_i) {
	cout << arr_tree[node_i] << ' ';
}

void preorder(int node_i) {
	int idx;
	if ((node_i < 32) &&
		(arr_tree[node_i] != NOT_DEF)) {
		idx = node_i * 2;
		visit(node_i);
		// left
		preorder(idx);
		// right
		preorder(idx + 1);
	}
}
void inorder(int node_i) {
	int idx;
	if ((node_i < 32) &&
		(arr_tree[node_i] != NOT_DEF)) {
		idx = node_i * 2;
		// left
		inorder(idx);
		visit(node_i);
		// right
		inorder(idx + 1);
	}
}
void postorder(int node_i) {
	int idx;
	if ((node_i < 32) &&
		(arr_tree[node_i] != NOT_DEF)) {
		idx = node_i * 2;
		// left
		postorder(idx);
		// right
		postorder(idx + 1);
		visit(node_i);
	}
}
