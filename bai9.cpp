#include <iostream>
using namespace std;

int main() {
    string s, p;
    cin >> s >> p;

    int n = s.size();
    int m = p.size();

    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    dp[0][0] = true;

    for (int j = 2; j <= m; j ++) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 2];
        }
    }

    // dp[i][j] là kiểm tra s[0..i-1] có khớp p[0..j-1] không

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            // th1: p[j - 1] là ký tự thường hoặc '.'

            if (p[j - 1] == s[i - 1] || p[j - 1] == '.') {
                dp[i][j] = dp[i - 1][j - 1];
            } else if (p[j - 1] == '*') {
                // th2: p[j - 1] là '*'
             
                // 2.1. Lặp 0 lần
                dp[i][j] = dp[i][j - 2];

                // 2.2. Lặp >= 1 ký tự
                if (p[j - 2] == s[i - 1] || p[j - 2] == '.') {
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                }
            }
        }
    }

    cout << (dp[n][m] ? "true" : "false");
}

// Độ phức tạp: O(n*m)