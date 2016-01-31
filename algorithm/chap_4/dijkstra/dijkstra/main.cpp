#include <iostream>

using namespace std;

#define INF 987654321
#define VT_CNT 6
#define GET_NUM(x) ((x)-'a')
#define GET_CHAR(x) ('a'+(x))
#define MIN(x,y) ((x>y)? (y):(x))

int adj[VT_CNT][VT_CNT] = { 0, };
int dist[VT_CNT] = { 0, };
int prv[VT_CNT] = { 0, };
bool visited[VT_CNT] = { false, };

int N;

void init();
void dijkstr(int start);
bool is_all_visited();
void print_path(int vt, int start);

int main() {
	char base;
	char target;
	int weight;
	int vt1_id;
	int vt2_id;
	cin >> N;

	init();
	for (int idx = 0; idx < N; idx++) {
		cin >> base >> target >> weight;
		vt1_id = GET_NUM(base);
		vt2_id = GET_NUM(target);
		adj[vt1_id][vt2_id] = weight;
	}
	vt1_id = GET_NUM('a');
	dijkstr(vt1_id);

	vt2_id = GET_NUM('f');

	cout << "shortest distance:" << dist[vt2_id] << endl;
	cout << "shortest path" << endl;
	print_path(vt2_id, vt1_id);

	return 0;
}

void init() {
	int row;
	int col;

	// init adjacency metrix
	for (row = 0; row < VT_CNT; row++) {
		for (col = 0; col < VT_CNT; col++) {
			adj[row][col] = INF;
		}
		adj[row][row] = 0;
	}
	// init dist metrix, prv metrix
	for (col = 0; col < VT_CNT; col++) {
		dist[col] = INF;
		prv[col] = 0;
		visited[col] = false;
	}
}

void print_path(int vt, int start) {
	char letter;
	if (vt != start) {
		print_path(prv[vt], start);
	}
	letter = GET_CHAR(vt);
	cout << letter << "->";
}

// all visited : true
bool is_all_visited() {
	int idx;
	bool is_flag = true;

	for (idx = 0; idx < VT_CNT; idx++) {
		if (visited[idx] == false) {
			is_flag = false;
			break;
		}
	}
	return is_flag;
}

void dijkstr(int start) {
	int idx;
	int min_dist_vt;
	int min_dist;

	visited[start] = true;
	for (idx = 0; idx < VT_CNT; idx++) {
		dist[idx] = adj[start][idx];
		prv[idx] = start;
	}

	while (is_all_visited() != true) {
		min_dist = INF;
		for (idx = 0; idx < VT_CNT; idx++) {
			if (visited[idx] == false) {
				if (dist[idx] < min_dist) {
					min_dist_vt = idx;
					min_dist = dist[idx];
				}
			}
		}
		visited[min_dist_vt] = true;

		for (idx = 0; idx < VT_CNT; idx++) {
			if (idx != min_dist_vt) {
				if (visited[idx] == false) {
					if (dist[idx] > (dist[min_dist_vt] + adj[min_dist_vt][idx])) {
						dist[idx] = dist[min_dist_vt] + adj[min_dist_vt][idx];
						prv[idx] = min_dist_vt;
					}
				}
			}
		}
	}
}