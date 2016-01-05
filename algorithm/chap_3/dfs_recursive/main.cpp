#include <iostream>

using namespace std;

int N;

int input[16];
int max_size = 16;
bool visited[8] = {false,};
int adjacency[8][8] = {0,};
int vertex_size = 7;
int stack[7] = {0,};
int top = -1;

void build_adjacency(int *data, int adj[][8]);
void dfs_recursive(int adj[][8], int vertex);

int main() {
    cin >> N;
    for (int idx; idx < 16; idx++) {
        cin >> input[idx];
    }

    build_adjacency(input, adjacency);
    dfs_recursive(adjacency, 1);
    return 0;
}

void build_adjacency(int *data, int adj[][8]) {
    int i = 0;
    int x = 0;
    int y = 0;

    for(i=0; i<max_size; i=i+2) {
        x = data[i];
        y = data[i+1];
        adj[x][y] = true;
        adj[y][x] = true;
    }
}

void dfs_recursive(int adj[][8], int vertex) {
    int i = 0;
    int x = 0;

    visited[vertex] = true;
    cout << vertex << '-';
    for(i=1; i<8; i++) {
        if(adj[vertex][i]) {
            if(visited[i] == false) {
                dfs_recursive(adj, i);
            }
        }
    }
}
