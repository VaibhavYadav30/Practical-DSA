#include <iostream>
using namespace std;

#define MAX 10

// ---------------------- ADJACENCY MATRIX SECTION -----------------------------

int cost[MAX][MAX];         // Adjacency matrix
int qu[MAX], front = 0, rear = 0;  // Queue for BFS
int stk[MAX], top = 0;      // Stack for DFS

int visited_bfs[MAX] = {0}; // Visited array for BFS
int visit_bfs[MAX] = {0};   // Temporary visit array for BFS queue
int visited_dfs[MAX] = {0}; // Visited array for DFS using matrix
int visit_dfs[MAX] = {0};   // Temporary visit array for DFS stack

// Function for BFS using adjacency matrix
void bfs_matrix(int n, int start) {
    int v = start;
    cout << "BFS Traversal (Adjacency Matrix):\n";
    cout << v << " ";
    visited_bfs[v] = 1;
    int k = 1;

    while (k < n) {
        for (int j = 0; j < n; j++) {
            if (cost[v][j] != 0 && visited_bfs[j] != 1 && visit_bfs[j] != 1) {
                visit_bfs[j] = 1;
                qu[rear++] = j;
            }
        }
        v = qu[front++];
        cout << v << " ";
        k++;
        visit_bfs[v] = 0;
        visited_bfs[v] = 1;
    }
}

// Function for DFS using adjacency matrix
void dfs_matrix(int n, int start) {
    int v = start;
    cout << "\nDFS Traversal (Adjacency Matrix):\n";
    cout << v << " ";
    visited_dfs[v] = 1;
    int k = 1;

    while (k < n) {
        for (int j = n - 1; j >= 0; j--) {
            if (cost[v][j] != 0 && visited_dfs[j] != 1 && visit_dfs[j] != 1) {
                visit_dfs[j] = 1;
                stk[top++] = j;
            }
        }
        v = stk[--top];
        cout << v << " ";
        k++;
        visit_dfs[v] = 0;
        visited_dfs[v] = 1;
    }
}

// ---------------------- ADJACENCY LIST SECTION -------------------------------

class lgra {
private:
    struct node1 {
        int vertex;
        node1* next;
    };

    node1* head[MAX];
    int visited[MAX];

public:
    lgra();
    void create();
    void dfs(int);
};

// Constructor to initialize visited array and heads
lgra::lgra() {
    for (int i = 0; i < MAX; i++) {
        head[i] = nullptr;
        visited[i] = 0;
    }
}

// Create undirected graph using adjacency list
void lgra::create() {
    int v1, v2;
    char ans;
    node1 *N, *temp;

    cout << "\n--- Create Adjacency List Graph ---\n";
    cout << "Enter edges (vertex numbers between 0 and " << MAX-1 << ")\n";
    do {
        cout << "Enter edge (u v): ";
        cin >> v1 >> v2;

        if (v1 >= MAX || v2 >= MAX) {
            cout << "Invalid Vertex Value\n";
            continue;
        }

        // Insert v2 into list of v1
        N = new node1{v2, nullptr};
        if (!head[v1]) {
            head[v1] = N;
        } else {
            temp = head[v1];
            while (temp->next) temp = temp->next;
            temp->next = N;
        }

        // Insert v1 into list of v2
        N = new node1{v1, nullptr};
        if (!head[v2]) {
            head[v2] = N;
        } else {
            temp = head[v2];
            while (temp->next) temp = temp->next;
            temp->next = N;
        }

        cout << "Add more edges? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
}

// DFS traversal using adjacency list
void lgra::dfs(int v1) {
    node1* temp;
    cout << v1 << " ";
    visited[v1] = 1;
    temp = head[v1];

    while (temp != nullptr) {
        if (!visited[temp->vertex]) {
            dfs(temp->vertex);
        }
        temp = temp->next;
    }
}

// ---------------------- MAIN FUNCTION ----------------------------------------

int main() {
    int n, m, i, j, k, start;

    // Input for adjacency matrix graph
    cout << "--- Create Adjacency Matrix Graph ---\n";
    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> m;

    cout << "Enter edges (u v):\n";
    for (k = 0; k < m; k++) {
        cin >> i >> j;
        cost[i][j] = 1;
        cost[j][i] = 1;
    }

    // Display adjacency matrix
    cout << "\nAdjacency Matrix:\n";
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cout << cost[i][j] << " ";
        }
        cout << endl;
    }

    // Perform BFS
    cout << "Enter starting vertex for BFS (Adjacency Matrix): ";
    cin >> start;
    bfs_matrix(n, start);

    // Perform DFS (Matrix)
    cout << "\nEnter starting vertex for DFS (Adjacency Matrix): ";
    cin >> start;
    dfs_matrix(n, start);

    // Create and perform DFS using adjacency list
    lgra g;
    g.create();

    cout << "\nEnter starting vertex for DFS (Adjacency List): ";
    cin >> start;

    if (start >= MAX) {
        cout << "Invalid Vertex\n";
    } else {
        cout << "DFS Traversal (Adjacency List): ";
        g.dfs(start);
    }

    return 0;
}
