#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    vector<int> leftMax(n), rightMax(n);

    leftMax[0] = h[0];
    for (int i = 1; i < n; i ++) {
        leftMax[i] = max(leftMax[i - 1], h[i]);
    }

    rightMax[n - 1] = h[n - 1];
    for (int i = n - 2; i >= 0; i --) {
        rightMax[i] = max(rightMax[i + 1], h[i]);
    }

    long long ans = 0;
    for (int i = 0; i < n; i ++) {
        ans += min(leftMax[i], rightMax[i]) - h[i];
    }

    cout << ans;
}

// Độ phức tạp: O(n)