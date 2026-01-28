#include <iostream>

using namespace std;

const long long MIN = -1e18;

int main() {
    int k, n, m;
    cin >> k >> n >> m;

    vector<int> a(k + 1), b(k + 1);
    for (int i = 1; i <= k; i ++) {
        cin >> a[i] >> b[i];
    }

    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, MIN));
    dp[0][0] = 0;

    // dp[i][x][y] là giá trị lớn nhất sau khi chọn i cụm với x phần tử từ a và y phần tử từ b
    // Vì dp[i] chỉ phụ thuộc vào dp[i - 1] => lược bỏ 1 chiều i

    for (int i = 1; i <= k; i ++) {
        for (int x = n; x >= 0; x --) {
            for (int y = m; y >= 0; y --) {
                long long cur = dp[x][y];
                if (cur == MIN) continue;

                // chọn i vào loại 1
                if (x + 1 <= n) {
                    dp[x + 1][y] = max(dp[x + 1][y], cur + a[i]);
                }

                // chọn i vào loại 2
                if (y + 1 <= m) {
                    dp[x][y + 1] = max(dp[x][y + 1], cur + b[i]);
                }
            }
        }
    }

    cout << dp[n][m];
}

// Độ phức tạp: O(k * n * m)