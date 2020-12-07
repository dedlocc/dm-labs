#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "vectors"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

void foo(vector<bool> &v, const size_t &p, vector<vector<bool>> &r, const bool &one = false)
{
    if (p == v.size()) {
        r.push_back(v);
        return;
    }

    v[p] = false;
    foo(v, 1 + p, r);

    if (!one) {
        v[p] = true;
        foo(v, 1 + p, r, true);
    }
}

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n;
    cin >> n;

    vector<bool> v(n);
    vector<vector<bool>> r;
    foo(v, 0, r);

    cout << r.size();
    for (const auto &e : r) {
        cout << '\n';
        for (const auto &b : e) {
            cout << b;
        }
    }

    return 0;
}