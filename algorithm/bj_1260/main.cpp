#include <iostream>

using namespace std;

int N;	// number of vertexes
int M;	// number of edges
int V;	// start v

bool check[1001];	// 1-base

typedef struct _edge {
	int p;
	int c;
} edge;

edge edge_list[20000];	// 0-base
int edge_idx[1001];	// 1-base

int queue[1001];
int front = 0;
int back = 0;

void quick_sort(int l, int r);
int lomuto_partition(int l, int r);
void swap(int a, int b);
void make_index_array();

void dfs(int x);
void bfs(int x);

int main() {
	cin >> N >> M >> V;
	int p;
	int c;
	for (int i = 0; i < M; i++) {
		cin >> p >> c;
		edge_list[i].p = p;
		edge_list[i].c = c;
		edge_list[i + M].p = c;
		edge_list[i + M].c = p;
	}
	M = M * 2;
	quick_sort(0, M - 1);
	make_index_array();
	dfs(V);
	for (int i = 1; i <= N; i++) {
		check[i] = false;
	}
	cout << endl;
	bfs(V);
	cout << endl;
	return 0;
}

void quick_sort(int l, int r) {
	if (l < r) {
		int p = lomuto_partition(l, r);
		quick_sort(l, p - 1);
		quick_sort(p + 1, r);
	}
}
int lomuto_partition(int l, int r) {
	edge x;
	x.p = edge_list[r].p;
	x.c = edge_list[r].c;
	int i = l - 1;
	int j;

	for (j = l; j < r; j++) {
		if (edge_list[j].p < x.p) {
			i++;
			swap(i, j);
		} else if (edge_list[j].p == x.p) {
			if (edge_list[j].c <= x.c) {
				i++;
				swap(i, j);
			}
		}
	}
	swap(i + 1, r);
	return i + 1;
}

void swap(int a, int b) {
	edge temp;

	temp.p = edge_list[a].p;
	temp.c = edge_list[a].c;

	edge_list[a].p = edge_list[b].p;
	edge_list[a].c = edge_list[b].c;

	edge_list[b].p = temp.p;
	edge_list[b].c = temp.c;
}

void make_index_array() {
	for (int i = 0; i < M; i++) {
		edge_idx[edge_list[i].p]++;
	}
	for (int i = 2; i <= N; i++) {
		edge_idx[i] += edge_idx[i - 1];
	}
}

void dfs(int x) {
	cout << x << ' ';
	check[x] = true;
	for (int i = edge_idx[x - 1]; i < edge_idx[x]; i++) {
		if (check[edge_list[i].c] == false) {
			dfs(edge_list[i].c);
		}
	}
}

void bfs(int x) {
	int v;
	cout << x << ' ';
	check[x] = true;
	queue[back++] = x;

	while (front != back) {
		v = queue[front++];
		for (int i = edge_idx[x - 1]; i < edge_idx[x]; i++) {
			if (check[edge_list[i].c] == false) {
				cout << edge_list[i].c << ' ';
				check[edge_list[i].c] = true;
				queue[back++] = edge_list[i].c;
			}
		}
	}
}
