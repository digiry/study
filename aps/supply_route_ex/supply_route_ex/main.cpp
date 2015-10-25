#include <iostream>

using namespace std;

#define INFINITE 999999

#define MIN(x,y) ((x>y)?y:x)

int map[100][100] = { 0, };
int x_d[4] = { -1,1,0,0 };
int y_d[4] = { 0,0,-1,1 };

int dist_array[10000] = { 0, };
int T;
int N;
int n_vertex = 0;
int visited[10000] = { 0, };
int previous[10000];

void initialize();
void dijkstra(int s);
bool is_all_visited();
int find_min_vertex();
void print_prev();

int main() {
	int tc;
	char depth;
	int x;
	int y;

	cin >> T;
	for (tc = 0; tc < T; tc++) {
		cin >> N;
		for (x = 0; x < N; x++) {
			for (y = 0; y < N; y++) {
				cin >> depth;
				map[x][y] = depth-'0';
			}
		}

		n_vertex = N * N;

		initialize();
		dijkstra(0);

		cout << '#' << tc + 1 << ' ' << dist_array[n_vertex-1] << ' ';
		print_prev();
	}

	return 0;
}

void initialize() {
	for (int i = 0; i < n_vertex; i++) {
		dist_array[i] = INFINITE;
		visited[i] = 0;
		previous[i] = 0;
	}
}

void dijkstra(int s) {
	int i;
	int target;
	int other;
	int row;
	int col;
	int row2;
	int col2;
	int di = 0;
	visited[s] = 1;

	// start vertex
	dist_array[0] = 0;
	// down vertex
	dist_array[1] = map[1][0];
	// right vertex
	dist_array[2] = map[0][1];
	for (i = 3; i < n_vertex; i++) {
		dist_array[i] = INFINITE;
	}

	while (is_all_visited() != true) {
		target = find_min_vertex();
		visited[target] = 1;
		//cout << "visit:" << target << endl;
		row = target / N;
		col = target % N;
		for (di = 0; di < 4; di++) {
			row2 = row + x_d[di];
			col2 = col + y_d[di];
			if ((0 <= row2) && (row2 <= N - 1) && 
				(0 <= col2) && (col2 <= N - 1)) {
				other = (row2 * N) + col2;
				//cout << "neighbor[" << other << "(" << row2 << "," << col2 << ")]:" << dist_array[other] <<
				//	"vs" << dist_array[target] + map[row2][col2] << endl;
				if (dist_array[other] > dist_array[target] + map[row2][col2]) {
					dist_array[other] = dist_array[target] + map[row2][col2];
					previous[other] = target;
				}
				//dist_array[other] = MIN(dist_array[other], dist_array[target] + map[row2][col2]);
			}
		}
		
	}
}

int find_min_vertex() {
	int i;
	int min_dist=INFINITE;
	int min_i = -1;

	for (i = 0; i < n_vertex; i++) {
		if (visited[i] == 0) {
			if (dist_array[i] < min_dist) {
				min_dist = dist_array[i];
				min_i = i;
			}
		}		
	}

	return min_i;
}

bool is_all_visited() {
	bool is_visited = true;
	for (int i = 0; i < n_vertex; i++) {
		if (visited[i] == 0) {
			is_visited = false;
			break;
		}
	}
	return is_visited;
}

void print_prev() {
	int target = n_vertex - 1;
	cout << ':' << target << '-';
	while (true) {
		target = previous[target];
		cout << target << '-';
		if (target == 0) {
			break;
		}
	}
	cout << endl;
}