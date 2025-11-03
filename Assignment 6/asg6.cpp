#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Item {
    string name;
    int value;
    int weight;
};

void solveKnapsack(int W, const vector<Item>& items) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Fill the DP table
    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= W; ++w) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(items[i - 1].value + dp[i - 1][w - items[i - 1].weight],
                               dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "\nOptimal Solution:\n";
    cout << "Maximum Utility Value: " << dp[n][W] << endl;
    cout << "Items to include in the truck:\n";
    
    // Backtrack to find items
    int maxValue = dp[n][W];
    int w = W;
    for (int i = n; i > 0 && maxValue > 0; --i) {
        if (maxValue != dp[i - 1][w]) {
            // This item was included
            cout << "- " << items[i - 1].name << " (Value: "
                 << items[i - 1].value << ", Weight: "
                 << items[i - 1].weight << ")" << endl;
                 
            maxValue -= items[i - 1].value;
            w -= items[i - 1].weight;
        }
    }
    cout << "----------------------------------------\n";
}

int main() {
    int truckCapacity;
    cout << "Enter the truck's maximum weight capacity: ";
    cin >> truckCapacity;

    int n;
    cout << "Enter the number of available item types: ";
    cin >> n;

    vector<Item> availableItems(n);
    cout << "Enter the details for each item (name value weight):" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> availableItems[i].name >> availableItems[i].value >>
               availableItems[i].weight;
    }

    solveKnapsack(truckCapacity, availableItems);
    return 0;
}