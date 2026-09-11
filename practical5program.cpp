#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, W;

    cout << "Enter number of items: ";
    cin >> n;

    vector<int> weight(n), value(n);

    cout << "Enter weights: ";
    for (int i = 0; i < n; i++)
        cin >> weight[i];

    cout << "Enter values: ";
    for (int i = 0; i < n; i++)
        cin >> value[i];

    cout << "Enter capacity: ";
    cin >> W;

    // 1D DP array: dp[w] = best profit using items processed so far, capacity w
    vector<int> dp(W + 1, 0);

    // choice[i][w] = true if item i was picked while filling capacity w
    vector<vector<bool>> choice(n, vector<bool>(W + 1, false));

    for (int i = 0; i < n; i++) {
        // traverse capacity backwards so each item is used at most once
        for (int w = W; w >= weight[i]; w--) {
            int profitWith = value[i] + dp[w - weight[i]];
            if (profitWith > dp[w]) {
                dp[w] = profitWith;
                choice[i][w] = true;
            }
        }
    }

    cout << "\nMaximum Profit = " << dp[W] << endl;

    // Reconstruct selected items using the choice table
    cout << "Selected Items: ";
    vector<int> selectedIdx;
    int remaining = W;
    for (int i = n - 1; i >= 0; i--) {
        if (choice[i][remaining]) {
            selectedIdx.push_back(i);
            remaining -= weight[i];
        }
    }

    for (int i = (int)selectedIdx.size() - 1; i >= 0; i--)
        cout << "Item " << (selectedIdx[i] + 1) << " ";

    cout << "\nSelected Weights: ";
    for (int i = (int)selectedIdx.size() - 1; i >= 0; i--)
        cout << weight[selectedIdx[i]] << " ";

    cout << endl;
    return 0;
}
