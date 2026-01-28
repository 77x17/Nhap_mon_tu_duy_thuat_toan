#include <iostream>
#include <vector>
using namespace std;

struct Point { long long x, y; };

long long cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x; 
}

int main() {
    int n; cin >> n;
    vector<Point> p(2 * n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i].x >> p[i].y;
        p[i + n] = p[i]; // nhân đôi
    }
    
    // prefix area
    vector<long long> pref(2 * n + 1, 0);
    for (int i = 1; i < 2 * n; i++) {
        pref[i + 1] = pref[i] + cross(p[i], p[i + 1]);
    }
    long long total = llabs(pref[n + 1] - pref[1]);
    long long best = LLONG_MAX;
    int ans_i = 1, ans_j = 3;
    
    for (int i = 1; i <= n; i++) {
        int j = i + 2;
        while (j <= i + n - 2) {
            long long cur  = llabs(pref[j] - pref[i] + cross(p[j], p[i]));
            long long diff = llabs(total - 2 * cur);

            if (diff < best) {
                best = diff;
                ans_i = i;
                ans_j = j;
            }

            long long next = llabs(pref[j + 1] - pref[i] + cross(p[j + 1], p[i]));
            if (llabs(total - 2 * next) > diff) break;

            j++;
        }
    }

    ans_i = (ans_i - 1) % n + 1;
    ans_j = (ans_j - 1) % n + 1;

    cout << ans_i << " " << ans_j << "\n";
    return 0;
}

