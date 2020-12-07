#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "telemetry"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

void foo(vector<size_t> &v, const size_t &k, const size_t &p, vector<bool> &r)
{
    if (p == v.size()) {
        for (const auto &b : v) {
            cout << +b;
        }
        cout << '\n';
        return;
    }

    if (!r[p]) {
        for (size_t i = 0; i < k; ++i) {
            v[p] = i;
            foo(v, k, 1 + p, r);
        }
    } else {
        for (size_t i = k - 1; i < k; --i) {
            v[p] = i;
            foo(v, k, 1 + p, r);
        }
    }

    r[p] = !r[p];
}

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n, k;
    cin >> n >> k;

    vector<size_t> v(n);
    vector<bool> r(n);
    foo(v, k, 0, r);

    return 0;
}