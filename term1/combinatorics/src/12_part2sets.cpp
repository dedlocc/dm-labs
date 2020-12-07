#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "part2sets"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

void foo(vector<size_t> &v, const size_t &k, const size_t &p, const size_t &q)
{
    if (p == v.size()) {
        if (q != k) {
            return;
        }

        vector<set<size_t>> u(k);
        for (size_t i = 0; i < v.size(); ++i) {
            u[v[i]].insert(1 + i);
        }

        for (const auto &i : u) {
            for (const auto &j : i) {
                cout << j << ' ';
            }
            cout << '\n';
        }
        cout << '\n';
        return;
    }

    for (size_t i = 0; i <= q; ++i) {
        v[p] = i;
        foo(v, k, 1 + p, (i == q) + q);
    }
}

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n, k;
    cin >> n >> k;

    vector<size_t> v(n);
    foo(v, k, 0, 0);

    return 0;
}
