#include <iostream>

using namespace std;

int N;
int M;

bool check[1001] = { false, };	// 1-base

typedef struct _edge {
	int p;
	int c;
} edge;

edge edge_list[499500] = { 0, };	// 0-base
int edge_idx[1001] = { 0, };	// 1-base

int conn_count = 0;

void quick_sort(int l, int r);
int lomuto_partition(int l, int r);
void swap(int a, int b);
void make_index_array();

void dfs(int x);

int main() {
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		cin >> edge_list[i].p >> edge_list[i].c;
	}

	quick_sort(0, M - 1);
	make_index_array();

	conn_count = 0;
	for (int i = 1; i <= N; i++) {
		if (check[i] == false) {
			dfs(i);
			conn_count++;
		}
	}

	cout << conn_count << endl;

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
		}
		else if (edge_list[j].p == x.p) {
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
	//cout << x << ' ';
	check[x] = true;
	for (int i = edge_idx[x - 1]; i < edge_idx[x]; i++) {
		if (check[edge_list[i].c] == false) {
			dfs(edge_list[i].c);
		}
	}
}


/*
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
struct Edge {
	int from, to;
};
Edge edge[499501];
int cnt[1001];
bool check[1001];
int conn_count = 0;
bool cmp(const Edge &u, const Edge &v) {
	if (u.from == v.from) {
		return u.to < v.to;
	}
	else {
		return u.from < v.from;
	}
}
void dfs(int node) {
	check[node] = true;
	//printf("%d ",node);
	for (int i = cnt[node - 1]; i<cnt[node]; i++) {
		int next = edge[i].to;
		if (check[next] == false) {
			dfs(next);
		}
	}
}
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i<m; i++) {
		scanf("%d %d", &edge[i].from, &edge[i].to);
	}
	sort(edge, edge + m, cmp);
	for (int i = 0; i<m; i++) {
		cnt[edge[i].from] += 1;
	}
	for (int i = 1; i <= n; i++) {
		cnt[i] += cnt[i - 1];
	}
	conn_count = 0;
	for (int i = 1; i <= n; i++) {
		if (check[i] == false) {
			dfs(i);
			conn_count++;
		}
	}

	printf("%d\n", conn_count);

	return 0;
}

*/