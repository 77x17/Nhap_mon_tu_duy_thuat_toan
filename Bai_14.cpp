#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
using namespace std;

struct Point {
    long long x, y;
};

long long triangleArea(Point a, Point b, Point c) {
    return abs((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
}

long long polygonArea(vector<Point> &points) {
    long long area = 0;
    int n = points.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += points[i].x * points[j].y;
        area -= points[j].x * points[i].y;
    }
    return abs(area);
}

int main() {
    int n; cin >> n;
    vector<Point> polygon(n);
    for (int i = 0; i < n; ++i) {
        cin >> polygon[i].x >> polygon[i].y;
    }

    long long totalArea = polygonArea(polygon);
    long long bestDiff = totalArea;
    int bestI = 0, bestJ = 2;

    for (int i = 0; i < n; ++i) {
        long long currentArea = triangleArea(polygon[i], polygon[(i + 1) % n], polygon[(i + 2) % n]);
        int j = (i + 2) % n;
        while (true) {
            int nextJ = (j + 1) % n;
            if (nextJ == i) break;

            long long addArea = triangleArea(polygon[i], polygon[j], polygon[nextJ]);
            long long currentDiff = abs(totalArea - 2 * currentArea);
            long long nextDiff = abs(totalArea - 2 * (currentArea + addArea));

            if (currentDiff < bestDiff) {
                bestDiff = currentDiff;
                bestI = i;
                bestJ = j;
            }

            if (nextDiff <= currentDiff) {
                currentArea += addArea;
                j = nextJ;
            }
            else {
                if (nextDiff < bestDiff) {
                    bestDiff = nextDiff;
                    bestI = i;
                    bestJ = j;
                }
                
                break;
            }

        }
    }

    cout << bestI + 1 << ' ' << bestJ + 1 << '\n';
    
    return 0;
}