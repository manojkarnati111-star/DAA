#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n, amount;

    // Number of different coins
    cout << "Enter number of coin types: ";
    cin >> n;

    vector<int> coins(n);

    // Coin values
    cout << "Enter coin values: ";
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    // Amount to exchange
    cout << "Enter the amount: ";
    cin >> amount;

    // DP array
    vector<int> dp(amount + 1, INT_MAX);

    // Base case
    dp[0] = 0;

    // Find minimum coins for each amount
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coins[j]] + 1);
            }
        }
    }

    // Display result
    if (dp[amount] == INT_MAX) {
        cout << "Coin exchange is not possible." << endl;
    } else {
        cout << "Minimum number of coins required = "
             << dp[amount] << endl;
    }

    return 0;
}
