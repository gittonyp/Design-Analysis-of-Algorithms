#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;
const int INF = numeric_limits<int>::max();

void findOptimalRoute(int N, const vector<vector<int>>& costMatrix) {
    vector<int> dp(N, 0);
    vector<int> path(N, 0);

    for (int i = N - 2; i >= 0; --i) {
        dp[i] = INF;
        for (int j = i + 1; j < N; ++j) {
            if (costMatrix[i][j] != INF) {
                if (dp[j] != INF) {
                    int cost = costMatrix[i][j] + dp[j];
                    if (cost < dp[i]) {
                        dp[i] = cost;
                        path[i] = j;
                    }
                }
            }
        }
    }

    // Output the results
    cout << "\n----------------------------------------\n";
    if (dp[0] == INF) {
        cout << "No route found from source to destination." << endl;
    } else {
        cout << "Minimum Delivery Cost: " << dp[0] << endl;
        cout << "Optimal Route Path: ";
        
        int currentNode = 0;
        while (currentNode != N - 1 && path[currentNode] != 0) {
            cout << currentNode << " -> ";
            currentNode = path[currentNode];
        }
        cout << N - 1 << endl;
    }
    cout << "----------------------------------------\n";
}

int main() {
    int N, E;
    cout << "Enter the total number of nodes: ";
    cin >> N;
    cout << "Enter the total number of routes (edges): ";
    cin >> E;

    vector<vector<int>> costMatrix(N, vector<int>(N, INF));

    cout << "Enter details for each route (source destination cost):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v, cost;
        cin >> u >> v >> cost;
        if (u >= 0 && u < N && v >= 0 && v < N) {
            costMatrix[u][v] = cost;
        }
    }

    findOptimalRoute(N, costMatrix);
    return 0;
}