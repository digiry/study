#include <iostream>

using namespace std;

int input[] = {1,2,1,3,2,4,2,5,4,6,5,6,6,7,3,7};
int max_size = 16;
bool visited[8] = {false,};
int adjacency[8][8] = {0,};
int vertex_size = 7;
int stack[7] = {0,};
int top = -1;

void build_adjacency(int *data, int adj[][8]);
void dfs_recursive(int adj[][8], int vertex);

int main() {
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