#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class FenwickTree {
    vector<int> tree;
    int size;

public:
    FenwickTree(int size) {
        this->size = size;
        tree.assign(size + 1, 0);
    };

    void update(int index, int value) {
        while (index <= size) {
            tree[index] += value;
            index += index & -index;
        }
    }

    int query(int index) {
        int sum = 0;
        while (index >= 1) {
            sum += tree[index];
            index -= index & -index;
        }
        return sum;
    }
};

int main() {
    int n; cin >> n;
    vector<int> arr(n);
    for (int &x : arr) cin >> x;
    vector<int> sorted = arr;
    sort(sorted.begin(),sorted.end());
    sorted.erase(unique(sorted.begin(),sorted.end()), sorted.end());
    int maxValue = 0;
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        c[i] = lower_bound(sorted.begin(),sorted.end(), arr[i]) - sorted.begin() + 1;
        maxValue = max(maxValue, c[i]);
    }

    FenwickTree fenwick(maxValue);
    long long result = 0;
    for (int i = n - 1; i >= 0; --i) {
        result += fenwick.query(c[i] - 1);
        fenwick.update(c[i], 1);
    }
    cout << result << '\n';
}
