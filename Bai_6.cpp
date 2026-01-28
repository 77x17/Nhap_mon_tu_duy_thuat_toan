#include <iostream>
#include <vector>

using namespace std;

vector<int> mergeTwoSortedArrays(const vector<int> &a, const vector<int> &b) {
    vector<int> result;
    int i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] <= b[j]) 
            result.push_back(a[i++]);
        else 
            result.push_back(b[j++]);
    }
    while (i < a.size()) 
        result.push_back(a[i++]);
    while (j < b.size()) 
        result.push_back(b[j++]);
    return result;
}

vector<int> mergeKSortedArrays(vector<vector<int>> &lists) {
    int k = lists.size();
    if (k == 1) return lists[0];
    while (k > 1) {
        for (int i = 0; i < k / 2; ++i) {
            lists[i] = mergeTwoSortedArrays(lists[i], lists[k - 1 - i]);
        }
        k = (k + 1) / 2;
    }
    return lists[0];
}

int main() {
    int k; cin >> k;
    vector<vector<int>> lists(k);
    for (int i = 0; i < k; ++i) {
        int x; while (cin >> x) {
            lists[i].push_back(x);
            if (cin.peek() == '\n') break;
        }
    }

    vector<int> result = mergeKSortedArrays(lists);

    for (int x : result) cout << x << ' ';
    return 0;
}
