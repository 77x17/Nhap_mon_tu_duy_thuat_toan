#include <iostream>
#include <vector>
#include <algorithm>   
#include <climits>
using namespace std;

inline long long Min(long long a, long long b) {
    return a < b ? a : b;
}

int n;
long long T;
vector<long long> h;

bool check(long long X) {
    vector<long long> L(n), R(n);

    // build L
    L[0] = h[0];
    for (int i = 1; i < n; i++)
        L[i] = Min(h[i], L[i-1] + 1);

    // build R
    R[n-1] = h[n-1];
    for (int i = n-2; i >= 0; i--)
        R[i] = Min(h[i], R[i+1] + 1);

    long long best = LLONG_MAX;

    for (int i = 0; i < n; i++) {
        if (h[i] < X) continue;

        long long cost = h[i] - X;

        // left side
        for (int j = i-1, cur = X+1; j >= 0; j--, cur++) {
            long long allowed = Min(L[j], cur);
            if (allowed > h[j]) break;
            cost += h[j] - allowed;
            if (cost > T) break;
        }

        // right side
        for (int j = i+1, cur = X+1; j < n; j++, cur++) {
            long long allowed = Min(R[j], cur);
            if (allowed > h[j]) break;
            cost += h[j] - allowed;
            if (cost > T) break;
        }

        best = Min(best, cost);
    }

    return best <= T;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> T;
    h.resize(n);

    long long mn = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        mn = Min(mn, h[i]);
    }

    long long L = mn - T;  
    long long R = mn;
    long long ans = mn;

    while (L <= R) {
        long long mid = (L + R) / 2;
        if (check(mid)) {
            ans = mid;
            R = mid - 1;
        } else {
            L = mid + 1;
        }
    }

    cout << ans;
    return 0;
}

// Độ phức tạp: O(n log (max(h)))
// Ý tưởng: Sử dụng binary search để tìm chiều cao mục tiêu X
// Với mỗi X, ta kiểm tra xem có thể giảm các cột về chiều cao X
// với tổng chi phí không vượt quá T hay không
// Bằng cách duyệt từng cột làm điểm thấp nhất và tính chi phí giảm
// các cột bên trái và bên phải sao cho không vượt quá X
