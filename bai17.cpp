#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    vector<char> digit(n);

    queue<int> q;

    int start = 1 % n;

    // Nếu x % n = y % n => (x + k*n) % n = (y + k*n) % n với mọi k >= 0

    q.push(start);
    visited[start] = true;
    digit[start] = '1';

    int found = -1;
    int level = 1;

    while (!q.empty() && level <= 9) {
        int sz = q.size();
        while (sz --) {
            int u = q.front();
            q.pop();

            if (u == 0) {
                found = u;
                break;
            }

            for (char d : {'0', '1'}) {
                int v = (u * 10 + (d - '0')) % n;
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    digit[v] = d;
                    q.push(v);
                }
            }
        }
        if (found != -1) break;
        level ++;
    }

    if (!visited[0]) return 0;

    string res;
    for (int r = 0; r != -1; r = parent[r]) {
        res += digit[r];
    }
    reverse(res.begin(), res.end());

    cout << res;
}