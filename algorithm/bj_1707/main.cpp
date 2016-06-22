#include <cstdio>

using namespace std;

int N;	// number of vertexes
int M;	// number of edges
int T;

int color_list[20001];	// 1-base

typedef struct _edge {
	int p;
	int c;
} edge;

edge edge_list[400000];	// 0-base
int n_edge_list = 0;
int edge_idx[20001];	// 1-base

void quick_sort(int l, int r);
int lomuto_partition(int l, int r);
void swap(int a, int b);
void make_index_array();

void dfs(int x, int color);

int main() {
	int tc;
	scanf("%d\n", &T);

	for (tc = 0; tc < T; tc++) {
		scanf("%d %d", &N, &M);
		int p;
		int c;
		for (int i = 0; i < M; i++) {
			scanf("%d %d", &p, &c);
			edge_list[i].p = p;
			edge_list[i].c = c;
			edge_list[i + M].p = c;
			edge_list[i + M].c = p;
		}
		n_edge_list = M * 2;
		quick_sort(0, n_edge_list - 1);
		make_index_array();

		for (int i = 1; i <= N; i++) {
			if (color_list[i] == 0) {
				dfs(i, 1);
			}
		}

		bool is_bi_graph = true;
		for (int i = 1; i < N; i++) {
			for (int j = edge_idx[i - 1]; j < edge_idx[i]; j++) {
				if (color_list[edge_list[j].p] == color_list[edge_list[j].c]) {
					is_bi_graph = false;
				}
			}
		}
		printf("%s\n", ((is_bi_graph) ? "YES" : "NO"));

		for (int i = 1; i <= N; i++) {
			color_list[i] = 0;
			edge_idx[i] = 0;
		}
	}
	
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
	for (int i = 0; i < n_edge_list; i++) {
		edge_idx[edge_list[i].p]++;
	}
	for (int i = 2; i <= N; i++) {
		edge_idx[i] += edge_idx[i - 1];
	}
}

void dfs(int x, int color) {
	color_list[x] = color;
	for (int i = edge_idx[x - 1]; i < edge_idx[x]; i++) {
		if (color_list[edge_list[i].c] == false) {
			dfs(edge_list[i].c, 3 - color);
		}
	}
}

/*
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
vector<int> a[20001];
int color[20001];
void dfs(int node, int c) {
	color[node] = c;
	for (int i = 0; i<a[node].size(); i++) {
		int next = a[node][i];
		if (color[next] == 0) {
			dfs(next, 3 - c);
		}
	}
}
int main() {
	int t;
	scanf("%d\n", &t);
	while (t--) {
		int n, m;
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++) {
			a[i].clear();
			color[i] = 0;
		}
		for (int i = 0; i<m; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			a[u].push_back(v);
			a[v].push_back(u);
		}
		for (int i = 1; i <= n; i++) {
			if (color[i] == 0) {
				dfs(i, 1);
			}
		}
		bool ok = true;
		for (int i = 1; i <= n; i++) {
			for (int k = 0; k<a[i].size(); k++) {
				int j = a[i][k];
				if (color[i] == color[j]) {
					ok = false;
				}
			}
		}
		printf("%s\n", ok ? "YES" : "NO");
	}
	return 0;
}
*/