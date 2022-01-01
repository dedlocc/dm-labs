#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Graph
{
    explicit Graph(size_t n) : edges(n), marked(n)
    {}

    void addEdge(size_t from, size_t to)
    {
        edges[from].push_back(to);
    }

    const vector<size_t> *dfs(size_t root)
    {
        fill(marked.begin(), marked.end(), false);
        order.clear();

        dfsImpl(root);

        for (size_t u : edges[order.front()]) {
            if (u == root) {
                return &order;
            }
        }

        return nullptr;
    }

private:
    vector<vector<size_t>> edges;
    vector<bool> marked;
    vector<size_t> order;

    void dfsImpl(size_t u)
    {
        if (!marked[u]) {
            marked[u] = true;
            for (size_t v : edges[u]) {
                dfsImpl(v);
            }
            order.push_back(u);
        }
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    Graph g(n);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            char b;
            cin >> b;
            b == '1' ? g.addEdge(i, j) : g.addEdge(j, i);
        }
    }

    for (size_t i = 0; i < n; ++i) {
        if (auto ptr = g.dfs(i)) {
            for (auto it = ptr->rbegin(); it != ptr->rend(); ++it) {
                cout << *it + 1 << ' ';
            }
            break;
        }
    }

    return 0;
}