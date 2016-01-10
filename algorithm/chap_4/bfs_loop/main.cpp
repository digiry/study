#include <iostream>

using namespace std;

int input[];

int N;

int max_size = 16;
bool visited[8] = {false,};
int adjacency[8][8] = {0,};
int vertex_size = 8;
int queue[7] = {0,};
int rear = 0;
int front = 0;

void build_adjacency(int *data, int adj[][8]);

void init_queue();
void enqueue(int item);
int dequeue();
bool is_queue_empty();
void bfs_loop(int adj[][8], int vertex);

int main() {
    cin >> N;
    for (int idx; idx < N; idx++) {
        cin >> input[idx];
    }
    build_adjacency(input, adjacency);
    bfs_loop(adjacency, 1);
    return 0;
}

void init_queue() {
    rear = 0;
    front = 0;
}
void enqueue(int item) {
    queue[rear++] = item;
}
int dequeue() {
    return queue[front++];
}
bool is_queue_empty() {
    bool is_empty = false;
    if(rear == front) {
        is_empty = true;
    }
    return is_empty;
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

void bfs_loop(int adj[][8], int vertex) {
    int target = 0;
    int neighbor = 0;
    int i = 0;

    init_queue();
    enqueue(vertex);
    visited[vertex] = true;
    cout << vertex << '-';

    while(is_queue_empty() != true) {
        target = dequeue();
        for(i=1; i<vertex_size; i++) {
            if(adj[target][i]) {
                neighbor = i;
                if(visited[neighbor] == false) {
                    enqueue(neighbor);
                    visited[neighbor] = true;
                    cout << neighbor << '-';
                }
            }
        }
    }
}
