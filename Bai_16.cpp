#include <iostream>
#include <vector>
using namespace std;

int n;
vector<vector<int>> adj;
vector<bool> visited;
vector<int>  subTree;
int result;

void dfs(int u) {
    visited[u] = true;
    subTree[u] = 1;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
            subTree[u] += subTree[v];

            result += subTree[v] * (n - subTree[v]);
        }
    }
}

int main() {
    cin >> n; 
    adj.assign(n + 1, vector<int>());

    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    visited.assign(n + 1, false);
    subTree.assign(n + 1, 0);

    dfs(1);

    cout << result << '\n';

    return 0;
}
