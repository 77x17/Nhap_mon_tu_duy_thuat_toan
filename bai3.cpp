#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool cmp(const pair<long long, int> &a, const pair<long long, int> &b) {
    return a.first < b.first;
}

int main() {
    int m, n;
    cin >> m >> n;

    vector<pair<long long, int>> a(m);
    vector<pair<long long, int>> b(n);

    for (int i = 0; i < m; i++) {
        cin >> a[i].first;
        a[i].second = i + 1;
    }

    for (int i = 0; i < n; i++) {
        cin >> b[i].first;
        b[i].second = i + 1;
    }

    sort(b.begin(), b.end(), cmp);

    long long min_diff = 1e18;
    int res_a = -1, res_b = -1;

    for (int i = 0; i < m; i++) {
        int left = 0, right = n - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            long long sum = a[i].first + b[mid].first;
            long long diff = llabs(sum);

            if (diff < min_diff) {
                min_diff = diff;
                res_a = a[i].second;
                res_b = b[mid].second;
            }

            if (sum < 0)
                left = mid + 1;
            else
                right = mid - 1;
        }
    }

    cout << res_a << " " << res_b << endl;
}

// độ phức tạp hiện tại là O(m log n)
// Dùng 2 con trỏ để giảm độ phức tạp xuống O(m + n)
// Hai con trỏ i, j lần lượt duyệt mảng a và b
// Nếu a[i] + b[j] == 0 => kết quả tốt nhất
// Nếu a[i] + b[j] < 0 => tăng i để tăng tổng lên
// Nếu a[i] + b[j] > 0 => giảm j để giảm tổng xuống
// Cách này hoạt động nêu mảng a và b đã được sắp xếp