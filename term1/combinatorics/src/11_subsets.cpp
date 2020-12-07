#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "subsets"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

void foo(vector<size_t> &v, const size_t &n)
{
    for (const auto &e : v) {
        cout << e << ' ';
    }
    cout << '\n';

    if (!v.empty() && n == v.back()) {
        return;
    }

    for (size_t i = 1; i <= n; ++i) {
        if (v.empty() || v.back() < i) {
            v.push_back(i);
            foo(v, n);
            v.pop_back();
        }
    }
}

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n;
    cin >> n;

    vector<size_t> v;

    foo(v, n);

    return 0;
}
