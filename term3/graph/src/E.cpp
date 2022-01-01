#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<unordered_set<size_t>> edges(n);

    for (size_t i = 1; i < n; ++i) {
        size_t u, v;
        cin >> u >> v;
        --u; --v;
        edges[u].insert(v);
        edges[v].insert(u);
    }

    priority_queue<size_t, vector<size_t>, greater<>> q;
    for (size_t i = 0; i < n; ++i) {
        if (edges[i].size() == 1) {
            q.push(i);
        }
    }

    for (size_t i = 2; i < n; ++i) {
        const size_t u = q.top();
        q.pop();
        const size_t v = *edges[u].begin();
        cout << v + 1 << ' ';
        edges[v].erase(u);
        if (edges[v].size() == 1) {
            q.push(v);
        }
    }

    return 0;
}