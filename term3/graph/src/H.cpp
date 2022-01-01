#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

struct Polynomial
{
    Polynomial() = default;

    explicit Polynomial(size_t n) : v(n)
    {
        v.back() = 1;
    }

    friend Polynomial operator-(const Polynomial &p1, const Polynomial &p2)
    {
        Polynomial r;
        auto it1 = p1.v.begin(), it2 = p2.v.begin();
        while (it1 != p1.v.end() || it2 != p2.v.end()) {
            auto &e = r.v.emplace_back();
            if (it1 != p1.v.end()) {
                e += *it1++;
            }
            if (it2 != p2.v.end()) {
                e -= *it2++;
            }
        }
        return r;
    }

    friend ostream &operator<<(ostream &out, const Polynomial &p)
    {
        out << p.v.size() << '\n';
        for (auto it = p.v.rbegin(); it != p.v.rend(); ++it) {
            out << *it << ' ';
        }
        return out << 0;
    }

private:
    vector<int> v;
};

struct Graph
{
    explicit Graph(size_t n) : edges(n)
    {}

    void addEdge(size_t from, size_t to)
    {
        edges[from].insert(to);
        edges[to].insert(from);
    }

    [[nodiscard]] Graph remove(size_t u, size_t v) const
    {
        Graph g = *this;
        g.edges[u].erase(v);
        g.edges[v].erase(u);
        return g;
    }

    [[nodiscard]] Graph contract(size_t u, size_t v) const
    {
        if (u > v) {
            swap(u, v);
        }
        Graph g(edges.size() - 1);
        for (size_t i = 0; i < edges.size(); ++i) {
            for (size_t j : edges[i]) {
                size_t ci = contractIndex(i, u, v);
                size_t cj = contractIndex(j, u, v);
                if (ci != cj) {
                    g.edges[ci].insert(cj);
                }
            }
        }
        return g;
    }

    [[nodiscard]] Polynomial chromaticPolynomial() const
    {
        for (size_t u = 0; u < edges.size(); ++u) {
            if (!edges[u].empty()) {
                size_t v = *edges[u].begin();
                return remove(u, v).chromaticPolynomial() - contract(u, v).chromaticPolynomial();
            }
        }
        return Polynomial(edges.size());
    }

private:
    vector<unordered_set<size_t>> edges;

    static size_t contractIndex(size_t old, size_t u, size_t v)
    {
        if (old == v) {
            return u;
        }
        if (old > v) {
            return old - 1;
        }
        return old;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    Graph g(n);

    for (size_t i = 0; i < m; ++i) {
        size_t u, v;
        cin >> u >> v;
        g.addEdge(u - 1, v - 1);
    }

    cout << g.chromaticPolynomial();

    return 0;
}