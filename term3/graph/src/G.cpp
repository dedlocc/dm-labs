#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> edges(n);

    for (size_t i = 0; i < m; ++i) {
        size_t a, b;
        cin >> a >> b;
        --a; --b;
        edges[b].push_back(a);
        edges[a].push_back(b);
    }

    vector<bool> visited(n);
    queue<size_t> bfs;
    vector<size_t> colors(n);

    visited[0] = true;
    bfs.push(0);
    size_t k = 0;

    while (!bfs.empty()) {
        size_t u = bfs.front();
        bfs.pop();
        unordered_set<size_t> set;
        for (size_t v : edges[u]) {
            if (!visited[v]) {
                visited[v] = true;
                bfs.push(v);
            } else if (colors[v]) {
                set.insert(colors[v]);
            }
        }
        for (size_t i = 1; i <= k; ++i) {
            if (set.find(i) == set.end()) {
                colors[u] = i;
                break;
            }
        }
        if (!colors[u]) {
            colors[u] = ++k;
        }
    }

    k = 0;
    for (auto &e : edges) {
        k = max(k, e.size());
    }

    cout << k + 1 - k % 2 << '\n';
    for (size_t color : colors) {
        cout << color << '\n';
    }

    return 0;
}