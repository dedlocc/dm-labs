#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "allvectors"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

void foo(vector<bool> &v, const size_t &p)
{
    if (p == v.size()) {
        for (const auto &b : v) {
            cout << b;
        }
        cout << '\n';
        return;
    }

    v[p] = false;
    foo(v, 1 + p);
    v[p] = true;
    foo(v, 1 + p);
}

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n;
    cin >> n;

    vector<bool> v(n);
    foo(v, 0);

    return 0;
}
