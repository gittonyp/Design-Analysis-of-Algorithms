#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Item {
    string name;
    double weight;
    double value;
    int priority; // Lower number means higher priority
    bool divisible;
    double ratio;
};

// Comparison function for sorting
bool cmp(const Item& a, const Item& b) {
    if (a.priority != b.priority)
        return a.priority < b.priority;
    return a.ratio > b.ratio;
}

int main() {
    double W;
    cout << "Enter maximum boat capacity (kg): ";
    cin >> W;

    vector<Item> items = {
        {"First Aid Box", 2.0, 70, 1, false},
        {"Medicine Kit", 6.0, 120, 1, false},
        {"Food Pack", 4.0, 80, 2, true},
        {"Water Bottles", 5.0, 50, 2, true},
        {"Blankets", 3.0, 40, 3, false}
    };

    // Compute value/weight ratio
    for (auto &item : items)
        item.ratio = item.value / item.weight;

    // Sort items
    sort(items.begin(), items.end(), cmp);

    // Display sorted items
    cout << fixed << setprecision(2);
    cout << "\nSorted Items (by priority, then value/weight):\n";
    cout << left << setw(20) << "Item"
         << setw(8) << "Weight"
         << setw(8) << "Value"
         << setw(8) << "Priority"
         << setw(12) << "Value/Weight"
         << setw(10) << "Type" << endl;
    cout << "---------------------------------------------------------------------\n";
    
    for (auto &item: items) {
        cout << setw(20) << item.name
             << setw(8) << item.weight
             << setw(8) << item.value
             << setw(8) << item.priority
             << setw(12) << item.ratio
             << setw(10) << (item.divisible ? "Divisible" : "Indivisible") << endl;
    }

    double totalValue = 0;
    double currentWeight = 0;

    cout << "\n--- Loading the Boat ---\n";

    for (auto &item : items) {
        if (currentWeight + item.weight <= W) {
            // Take the whole item
            currentWeight += item.weight;
            totalValue += item.value;
            cout << "Loaded: " << item.name << " (Weight: " << item.weight
                 << "kg, Value: " << item.value << ")\n";
        } else if (item.divisible) {
            // Take a fraction of the item
            double remainingWeight = W - currentWeight;
            if (remainingWeight > 0) {
                double fraction = remainingWeight / item.weight;
                totalValue += item.value * fraction;
                currentWeight += remainingWeight;
                cout << "Loaded: " << (fraction * 100) << "% of " << item.name
                     << " (Weight: " << remainingWeight << "kg, Value: "
                     << (item.value * fraction) << ")\n";
                break; // Boat is full
            }
        } else {
            // Cannot take fraction, skip
            cout << "Skipped: " << item.name << " (Weight: " << item.weight
                 << "kg) - Indivisible and too heavy.\n";
        }
        if (currentWeight == W) break;
    }

    cout << "\n--- Final Report ---\n";
    cout << "Total weight in boat: " << currentWeight << " kg\n";
    cout << "Total utility value: " << totalValue << "\n";

    return 0;
}