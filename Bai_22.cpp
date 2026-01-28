#include <iostream>
#include <vector>
using namespace std;

int n, m;
struct Edge { int to, id; };
vector<vector<Edge>> adj;
int timer = 0;
vector<int> cSize, num, low, result;

void dfs(int u, int parentId) {
    cSize[u] = 1;
    num[u] = low[u] = ++timer;
    for (const Edge &edge : adj[u]) {
        int v = edge.to, id = edge.id;
        if (id == parentId) continue;

        if (num[v]) {
            low[u] = min(low[u], num[v]);
        }
        else {
            dfs(v, id);
            cSize[u] += cSize[v];
            low[u] = min(low[u], low[v]);

            if (low[v] > num[u]) {
                result[id] = cSize[v] * (n - cSize[v]);
            }
        }
    }
}

int main() {
    cin >> n >> m;
    adj.assign(n + 1, vector<Edge>());
    for (int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back({ v, i });
        adj[v].push_back({ u, i });
    }

    cSize .assign(n + 1, 0);
    num   .assign(n + 1, 0);
    low   .assign(n + 1, 0);
    result.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (num[i] == 0) {
            dfs(i, -1);
        }
    }

    for (int i = 1; i <= n; ++i) 
        cout << result[i] << '\n';

    return 0;
}
