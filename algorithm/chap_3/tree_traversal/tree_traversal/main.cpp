#include <iostream>

using namespace std;

#define MAX_NODES 14

int N;

typedef struct __node {
	struct __node *left;
	struct __node *right;
	int value;
} node;

node node_tree[MAX_NODES] = { 0, };

void init_node_tree();
void visit(node *t_node);
void preorder(node *t_node);
void inorder(node *t_node);
void postorder(node *t_node);

int main() {
	int tc;
	int parent;
	int child;
	int idx;

	init_node_tree();
	cin >> N;

	
	for (tc = 0; tc < N; tc++) {
		cin >> parent >> child;
		node_tree[parent].value = parent;
		if (node_tree[parent].left == NULL) {
			node_tree[parent].left = &(node_tree[child]);
			node_tree[parent].left->value = child;
		}
		else {
			node_tree[parent].right = &(node_tree[child]);
			node_tree[parent].right->value = child;
		}
	}
	cout << "traverse tree by preorder:vLR" << endl;
	preorder(&(node_tree[1]));
	cout << endl << "traverse tree by inorder:LvR" << endl;
	inorder(&(node_tree[1]));
	cout << endl << "traverse tree by postorder:LRv" << endl;
	postorder(&(node_tree[1]));
	cout << endl;
	return 0;
}

void init_node_tree() {
	for (int idx = 0; idx < MAX_NODES; idx++) {
		node_tree[idx].left = NULL;
		node_tree[idx].right = NULL;
	}
}

void visit(node *t_node) {
	cout << t_node->value << ' ';
}

void preorder(node *t_node) {
	if (t_node != NULL) {
		visit(t_node);
		preorder(t_node->left);
		preorder(t_node->right);
	}
}
void inorder(node *t_node) {
	if (t_node != NULL) {
		inorder(t_node->left);
		visit(t_node);
		inorder(t_node->right);
	}
}
void postorder(node *t_node) {
	if (t_node != NULL) {
		postorder(t_node->left);
		postorder(t_node->right);
		visit(t_node);
	}
}