#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

using Edges = vector<vector<bool>>;

struct HamiltonianCycle
{
    HamiltonianCycle(size_t n, const Edges &edges) : edges(edges)
    {
        for (size_t i = 0; i < n; ++i) {
            q.push_back(i);
        }

        for (size_t i = n * 4; i > 0; --i) {
            if (!hasEdge(0, 1)) {
                size_t j;
                for (j = 2; !hasEdge(0, j) || !hasEdge(1, j + 1); ++j) {}
                reverse(j);
            }
            shift();
        }
    }

private:
    [[nodiscard]] bool hasEdge(size_t i, size_t j) const
    {
        return edges[q[i]][q[j]];
    }

    void reverse(size_t n)
    {
        auto begin = q.begin() + 1;
        ::reverse(begin, begin + static_cast<int>(n));
    }

    void shift()
    {
        q.push_back(q.front());
        q.pop_front();
    }

    friend ostream &operator<<(ostream &out, const HamiltonianCycle &hc)
    {
        for (size_t v : hc.q) {
            out << v + 1 << ' ';
        }
        return out;
    }

    const Edges &edges;
    deque<size_t> q;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    Edges edges(n, vector<bool>(n));

    for (size_t u = 1; u < n; ++u) {
        for (size_t v = 0; v < u; ++v) {
            char e;
            cin >> e;
            if (e == '1') {
                edges[u][v] = edges[v][u] = true;
            }
        }
    }

    cout << HamiltonianCycle(n, edges);

    return 0;
}