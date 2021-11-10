#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

vector<vector<pair<int, int>>> g;
vector<long long> l, pre, ans, len;
vector<vector<int>> ver;
set<pair<pair<int, int>, int>> q;
int INF = 1e9;

void Dijkstra() {
    while (!q.empty()) {
        auto p = *q.begin();
        q.erase(p);
        int v = p.first.second;
        for (auto to : g[v]) {
            int u = to.first;
            int w = to.second;
            if (l[u] > l[v] + w) {
                q.erase({ {l[u], u}, len[u] });
                l[u] = l[v] + w;
                q.insert({{l[u], u}, len[v] - 1});
                pre[u] = v;
                len[u] = len[v] - 1;
            }
            if (l[u] == l[v] + w) {
                if (len[v] + 1 < len[u]) {
                    pre[u] = v;
                    len[u] = len[v] - 1;
                }
            }
        }
    }
}

int main() {
    int n, m, s, f;
    cin >> n >> m >> s >> f;
    f--;
    s--;
    g.resize(n);
    pre.resize(n);
    ver.resize(n, vector<int>(n));
    l.resize(n, INF);
    len.resize(n, -INF);
    l[s] = 0;
    len[s] = 0;
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        g[a - 1].push_back({ b - 1, w });
        g[b - 1].push_back({ a - 1, w });
        ver[a - 1][b - 1] = i + 1;
        ver[b - 1][a - 1] = i + 1;
    }
    q.insert({{ 0, s }, 0});
    Dijkstra();
    if (l[f] == INF) {
        cout << -1;
    }
    else {
        cout << l[f] << '\n';
        ans.push_back(f);
        while (f != s) {
            f = pre[f];
            ans.push_back(f);
        }
        cout << ans.size() -2  << '\n';
        for (int i = ans.size() - 2; i > 0; i--) {
            cout << ans[i] + 1 << ' ';
        }
    }
    return 0;
}