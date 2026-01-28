#include <iostream>
using namespace std;

int main() {
    int s; cin >> s;
    for (int a = 0; a * a <= s; ++a) {
        for (int b = 0; b * b <= s; ++b) {
            if (a * a + b * b == s) {
                cout << 0 << ' ' << 0 << '\n';
                cout << a << ' ' << b << '\n';
                cout << a - b << ' ' << a + b << '\n';
                cout << -b << ' ' << a << '\n';
                return 0;
            }
        }
    }
    cout << "Impossible\n";
    return 0;
}
