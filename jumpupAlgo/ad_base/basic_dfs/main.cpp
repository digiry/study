#include <cstdio>

using namespace std;

int Vertex;
int Edges;

typedef struct _node {
	int p;
	int c;
} node;

node edge_list[20];
int edge_cnt_arr[11];
bool visits[9];

void swap(int a, int b);
void q_sort(int l, int r);
int lomuto_p(int l, int r);

void dfs(int vt);

int main() {
	int M;
	scanf("%d %d", &Vertex, &Edges);

	M = Edges;
	for (int i = 0; i < Edges; i++) {
		scanf(" %d %d", &(edge_list[i].p), &(edge_list[i].c));
		edge_list[i + M].p = edge_list[i].c;
		edge_list[i + M].c = edge_list[i].p;
	}
	M = M * 2;
	q_sort(0, M - 1);
	for (int i = 0; i < M; i++) {
		edge_cnt_arr[edge_list[i].p]++;
	}

	for (int i = 1; i <= Edges; i++) {
		edge_cnt_arr[i] = edge_cnt_arr[i - 1] + edge_cnt_arr[i];
	}

	dfs(1);
	printf("\n");
	return 0;
}

void swap(int a, int b) {
	node temp;

	temp.p = edge_list[a].p;
	temp.c = edge_list[a].c;

	edge_list[a].p = edge_list[b].p;
	edge_list[a].c = edge_list[b].c;

	edge_list[b].p = temp.p;
	edge_list[b].c = temp.c;
}

void q_sort(int l, int r) {
	int s = 0;
	if (l < r) {
		s = lomuto_p(l, r);
		q_sort(l, s - 1);
		q_sort(s + 1, r);
	}
}

int lomuto_p(int l, int r) {
	node x = edge_list[r];
	int i = l - 1;

	for (int j = l; j < r; j++) {
		if (x.p > edge_list[j].p) {
			i++;
			swap(i, j);
		}
		else if (x.p == edge_list[j].p) {
			if (x.c >= edge_list[j].c) {
				i++;
				swap(i, j);
			}
		}
	}
	swap(i + 1, r);
	return i + 1;
}

void dfs(int vt) {
	visits[vt] = true;
	printf("%d ", vt);
	for (int i = edge_cnt_arr[vt - 1]; i < edge_cnt_arr[vt]; i++) {
		if (visits[edge_list[i].c] == false) {
			dfs(edge_list[i].c);
		}
	}
}
