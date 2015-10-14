#include <iostream>

using namespace std;

int input[] = {1,2,1,3,2,4,2,5,4,6,5,6,6,7,3,7};
int max_size = 16;
bool visited[8] = {false,};
int adjacency[8][8] = {0,};
int vertex_size = 8;
int stack[7] = {0,};
int top = -1;

void build_adjacency(int *data, int adj[][8]);
void init_visited(bool *data);
void dfs_loop(int adj[][8], int vertex);
void init_stack();
void push(int data);
int pop();
bool is_stack_empty();

int main() {
    build_adjacency(input, adjacency);
    init_visited(visited);
    init_stack();
    cout << "dfs_loop" << endl;
    dfs_loop(adjacency, 1);

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

void init_visited(bool *data) {
    int i = 0;

    for(i=0; i<vertex_size; i++) {
        visited[i] = false;
    }
}

void init_stack() {
    top = -1;
}

void push(int data) {
    stack[++top] = data;
}

int pop() {
    return stack[top--];
}

bool is_stack_empty() {
    return (top == -1) ? true:false;
}

void dfs_loop(int adj[][8], int vertex) {
    int node = 0;
    int i = 0;
    push(vertex);
    while(is_stack_empty() != true) {
        node = pop();
        if(visited[node] == false) {
            visited[node] = true;
            cout << node << '-';
            for(i=1; i<vertex_size; i++) {
                if(adj[node][i]) {
                    if(visited[i] == false) {
                        push(i);
                    }
                }
            }
        }
    }
}