#include <iostream>
using namespace std;

const double PI = 3.14159265358979323846;

int main() {
    int x1, y1, x2, y2, R;
    cin >> x1 >> y1 >> x2 >> y2 >> R;

    double dx = x1 - x2;
    double dy = y1 - y2;
    double d = sqrt(dx * dx + dy * dy);

    double area;

    if (d >= 2*R) {
        area = 2 * PI * R * R;
    } else if (d == 0) {
        area = PI * R * R;
    } else {
        double intersection =
            2 * R * R * acos(d / (2 * R))
            - 0.5 * d * sqrt(4 * R * R - d * d);

        area = 2 * PI * R * R - intersection;
    }

    cout.precision(3);
    cout << fixed << area << endl;
}