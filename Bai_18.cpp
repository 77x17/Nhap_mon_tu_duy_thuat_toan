#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

string toString(const vector<int> &arr) {
    string result;
    for (int x : arr) {
        result += x + '0';
    }
    return result;
}

int main() {
    int n; cin >> n;
    vector<int> arr(n); 
    for (int i = 0; i < n; ++i) cin >> arr[i];

    vector<int> goal(n);
    for (int i = 0; i < n; ++i) goal[i] = i + 1;

    queue<pair<vector<int>, int>> q;
    unordered_map<string, bool> visited;

    q.push({ arr, 0 });
    visited[toString(arr)] = true;
    while (q.size()) {
        auto [current, steps] = q.front();
        q.pop();
        if (current == goal) {
            cout << steps << '\n';
            return 0;
        }

        for (int i = 2; i <= n; ++i) {
            vector<int> next = current;
            reverse(next.begin(), next.begin() + i);
            string key = toString(next);
            if (!visited[key]) {
                visited[key] = true;
                q.push({next, steps + 1});
            }
        }
    }
    
    return 0;
}
