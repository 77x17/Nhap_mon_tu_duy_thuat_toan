#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int main() {
    vector<int> p;
    string line; getline(cin, line);
    stringstream ss(line);
    int val;
    while (ss >> val) p.push_back(val);

    int n = p.size();

    unsigned long long y; cin >> y;

    vector<unsigned long long> factorial(n + 1, 1);
    for (int i = 1; i <= n; ++i) factorial[i] = factorial[i - 1] * i;

    vector<bool> used(n + 1, false);
    unsigned long long x = 1;
    for (int i = 0; i < n; ++i) {
        int count = 0;
        for (int v = 1; v < p[i]; ++v) {
            if (!used[v]) ++count;
        }
        x += count * factorial[n - i - 1];
        used[p[i]] = true;
    }
    cout << x << '\n';

    vector<int> nums;
    for (int i = 1; i <= n; ++i) nums.push_back(i);

    y--;
    vector<int> q(n);

    for (int i = 0; i < n; ++i) {
        unsigned long long f = factorial[n - i - 1];
        int index = y / f;
        q[i] = nums[index];
        nums.erase(nums.begin() + index);
        y %= f;
    } 
    for (int i = 0; i < n; ++i) {
        cout << q[i] << ' ';
    }

    return 0;
}
