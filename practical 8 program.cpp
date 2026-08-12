#include <iostream>
#include <vector>
#include <queue>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Graph
{
    int V;
    vector<vector<int>> adj;

public:

    // Constructor
    Graph(int vertices)
    {
        V = vertices;
        adj.resize(V);
    }

    // Add edge
    void addEdge(int u, int v)
    {
        if (u >= 0 && u < V && v >= 0 && v < V)
        {
            adj[u].push_back(v);
            adj[v].push_back(u);   // Undirected graph
        }
        else
        {
            cout << "Invalid edge: " << u << " " << v << endl;
        }
    }

    // DFS Utility Function
    void DFSUtil(int v, vector<bool>& visited)
    {
        visited[v] = true;
        cout << v << " ";

        for (int neighbor : adj[v])
        {
            if (!visited[neighbor])
            {
                DFSUtil(neighbor, visited);
            }
        }
    }

    // DFS
    void DFS(int start)
    {
        if (start < 0 || start >= V)
        {
            cout << "Invalid starting vertex!";
            return;
        }

        vector<bool> visited(V, false);
        DFSUtil(start, visited);
    }

    // BFS
    void BFS(int start)
    {
        if (start < 0 || start >= V)
        {
            cout << "Invalid starting vertex!";
            return;
        }

        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            cout << node << " ";

            for (int neighbor : adj[node])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }
};

int main()
{
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    if (V <= 0)
    {
        cout << "Number of vertices must be greater than 0.";
        return 0;
    }

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter edges (u v):\n";

    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int start;

    cout << "Enter starting vertex: ";
    cin >> start;

    // ---------------- DFS ----------------
    auto startDFS = high_resolution_clock::now();

    cout << "\nDFS Traversal: ";
    g.DFS(start);

    auto endDFS = high_resolution_clock::now();

    auto dfsTime =
        duration_cast<nanoseconds>(endDFS - startDFS);

    // ---------------- BFS ----------------
    auto startBFS = high_resolution_clock::now();

    cout << "\nBFS Traversal: ";
    g.BFS(start);

    auto endBFS = high_resolution_clock::now();

    auto bfsTime =
        duration_cast<nanoseconds>(endBFS - startBFS);

    // ---------------- Time ----------------
    cout << "\n\nExecution Time:";
    cout << "\nDFS: " << dfsTime.count() << " ns";
    cout << "\nBFS: " << bfsTime.count() << " ns";

    return 0;
}
