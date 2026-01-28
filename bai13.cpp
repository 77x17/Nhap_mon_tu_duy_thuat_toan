#include <iostream>
using namespace std;

struct Point {
    long long x, y;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Point> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }

    int need = (n - 2) / 2;
    const double PI = acos(-1);

    for (int i = 0; i < n; i++) {
        vector<pair<double,int>> angles;

        // Tính góc các điểm khác so với p[i]
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            double ang = atan2(
                p[j].y - p[i].y,
                p[j].x - p[i].x
            );
            angles.push_back({ang, j});
        }

        // Sort theo góc
        sort(angles.begin(), angles.end());

        int m = angles.size();

        // Nhân đôi mảng để xử lý vòng tròn
        for (int k = 0; k < m; k++) {
            angles.push_back({angles[k].first + 2 * PI, angles[k].second});
        }

        // Two pointers
        int r = 0;
        for (int l = 0; l < m; l++) {
            if (r < l) r = l;

            // Mở rộng r sao cho góc < pi
            while (r + 1 < l + m &&
                   angles[r + 1].first - angles[l].first < PI) {
                r++;
            }

            int cnt = r - l; // số điểm nằm bên trái

            if (cnt == need) {
                cout << i + 1 << " " << angles[l].second + 1;
                return 0;
            }
        }
    }

    return 0;
}
// Độ phức tạp: O(n^2 log n)