#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "matching"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

struct Matching
{
    explicit Matching(size_t n) : edges(n), visited(n), matching(n, NO_MATCHING)
    {
        vector<unsigned> w(n);

        for (auto &e : w) {
            cin >> e;
        }

        vector<size_t> order(n);
        iota(order.begin(), order.end(), 0);

        sort(order.begin(), order.end(), [&w](size_t l, size_t r) {
            return w[l] > w[r];
        });

        for (size_t i = 0; i < n; ++i) {
            size_t k;
            cin >> k;
            for (size_t j = 0; j < k; ++j) {
                size_t t;
                cin >> t;
                edges[i].push_back(--t);
            }
        }

        for (auto u : order) {
            fill(visited.begin(), visited.end(), false);
            dfs(u);
        }

        vector<size_t> reversedMatching(n, NO_MATCHING);
        for (size_t i = 0; i < n; ++i) {
            if (matching[i] != NO_MATCHING) {
                reversedMatching[matching[i]] = i;
            }
        }
        matching = reversedMatching;
    }

    bool dfs(size_t u)
    {
        if (u == NO_MATCHING) {
            return true;
        }
        if (!visited[u]) {
            visited[u] = true;
            for (auto v : edges[u]) {
                if (dfs(matching[v])) {
                    matching[v] = u;
                    return true;
                }
            }
        }
        return false;
    }

    vector<vector<size_t>> edges;
    vector<bool> visited;
    vector<size_t> matching;

    static constexpr size_t NO_MATCHING = -1;
};

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n;
    cin >> n;

    Matching m(n);

    for (auto e : m.matching) {
        cout << e + 1 << ' ';
    }

    return 0;
}