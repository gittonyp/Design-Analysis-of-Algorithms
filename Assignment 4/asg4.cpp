#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const int INT_MAX = numeric_limits<int>::max();
typedef pair<int, int> iPair;

void dijkstra(int src, const vector<vector<iPair>>& adj, vector<int>& dist, vector<int>& parent) {
    int V = adj.size();
    dist.assign(V, INT_MAX);
    parent.assign(V, -1);

    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

void printPath(int node, const vector<int>& parent) {
    vector<int> path;
    while (node != -1) {
        path.push_back(node);
        node = parent[node];
    }
    reverse(path.begin(), path.end());
    
    cout << "Optimal Path: ";
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;
}

int main() {
    int V, E;
    cout << "Enter number of intersections (vertices): ";
    cin >> V;
    cout << "Enter number of roads (edges): ";
    cin >> E;

    vector<vector<iPair>> graph(V);
    cout << "Enter roads (u v travel time):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // Assuming undirected roads
    }

    char update;
    cout << "Do you want to update travel times due to traffic? (y/n): ";
    cin >> update;
    while (update == 'y') {
        int u, v, w;
        cout << "Enter road to update (u v new_travel time): ";
        cin >> u >> v >> w;
        
        // Update edge u->v
        for (auto& edge : graph[u]) {
            if (edge.first == v) edge.second = w;
        }
        // Update edge v->u
        for (auto& edge : graph[v]) {
            if (edge.first == u) edge.second = w;
        }
        
        cout << "Update another road? (y/n): ";
        cin >> update;
    }

    int source;
    cout << "Enter ambulance start location (source): ";
    cin >> source;

    int H;
    cout << "Enter number of hospitals: ";
    cin >> H;
    vector<int> hospitals(H);
    cout << "Enter hospital node indices: ";
    for (int i = 0; i < H; i++) {
        cin >> hospitals[i];
    }

    vector<int> dist, parent;
    dijkstra(source, graph, dist, parent);

    int nearestHospital = -1, minTime = INT_MAX;
    for (int h : hospitals) {
        if (dist[h] < minTime) {
            minTime = dist[h];
            nearestHospital = h;
        }
    }

    if (nearestHospital == -1 || dist[nearestHospital] == INT_MAX) {
        cout << "No hospital reachable.\n";
    } else {
        cout << "\nNearest hospital is at node " << nearestHospital
             << " with estimated time " << minTime << " minutes.\n";
        printPath(nearestHospital, parent);
    }

    return 0;
}