#include <iostream>
using namespace std;

struct Edge {
    int u, v, w;
    bool inMST = false;
};

struct DSU {
    vector<int> parent;

    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootY] = rootX;
            return true;
        }
        return false;
    }
};

const int MAXN = 1e5 + 5;
vector<pair<int, int>> adj[MAXN];
const int Log = 17;
int up[Log][MAXN];
int mx[Log][MAXN];
int depth[MAXN];
int n, m, k;

void dfs(int u, int p, int w) {
    up[0][u] = p;
    mx[0][u] = w;
    
    for (auto [v, wt]: adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u, wt);
        }
    }
}

int getMaxEdge(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);

    int res = 0;

    int diff = depth[u] - depth[v];
    for (int i = 0; i < Log; i++) {
        if (diff & (1 << i)) {
            res = max(res, mx[i][u]);
            u = up[i][u];
        }
    }

    if (u == v) return res;

    for (int i = Log - 1; i >= 0; i--) {
        if (up[i][u] != up[i][v]) {
            res = max(res, mx[i][u]);
            res = max(res, mx[i][v]);
            u = up[i][u];
            v = up[i][v];
        }
    }

    res = max(res, mx[0][u]);
    res = max(res, mx[0][v]);
    return res;
}

int main() {
    cin >> n >> m >> k;
    vector<Edge> edges(m);

    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        return a.w < b.w;
    });

    DSU dsu(n);
    long long mstWeight = 0;

    for (auto &edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            mstWeight += edge.w;
            edge.inMST = true;
            adj[edge.u].push_back({edge.v, edge.w});
            adj[edge.v].push_back({edge.u, edge.w});
        }
    }

    depth[1] = 0;
    dfs(1, 0, 0);

    for (int i = 1; i < Log; i++) {
        for (int u = 1; u <= n; u++) {
            up[i][u] = up[i - 1][up[i - 1][u]];
            mx[i][u] = max(mx[i - 1][u], mx[i - 1][up[i - 1][u]]);
        }
    }

    vector <long long> results;

    for (auto &e: edges) {
        if (!e.inMST) {
            int maxEdge = getMaxEdge(e.u, e.v);
            long long newWeight = mstWeight - maxEdge + e.w;
            results.push_back(newWeight);
        }
    }

    sort(results.begin(), results.end());

    if (k == 1) cout << mstWeight;
    else cout << results[k - 2];
}

// Độ phức tạp:
// Xây dựng MST bằng Kruskal: O(m log m)
// Xây dựng bảng nhảy LCA: O(n log n)
// Truy vấn mỗi cạnh ngoài MST: O(m log n)
// Tổng độ phức tạp: O(m log m + n log n + m log n) ~ O(m log m)

// 2, 4
// 2 -> 3 -> 1 
// 4 -> 1