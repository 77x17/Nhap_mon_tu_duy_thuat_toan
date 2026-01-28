#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// k <= n <= 10^3
int main() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int max_gcd = 0;
    for (int i = 0; i <= n - k; i++) {
        int cr_gcd = a[i];
        for (int j = i + 1; j < i + k; j++) {
            cr_gcd = std::gcd(cr_gcd, a[j]);
        }
        max_gcd = max(max_gcd, cr_gcd);
    }

    cout << max_gcd << endl;
    return 0;
}

// Độ phức tạp: O(n * k)

// Nếu k <= n <= 10^5, ta có thể sử dụng cấu trúc dữ liệu Segment Tree hoặc bảng thưa để tối ưu việc tính GCD trong khoảng [i, i+k-1].
// Độ phức tạp: O(n log n) với Segment Tree hoặc O(n log n) để xây dựng bảng thưa và O(n) để truy vấn.

