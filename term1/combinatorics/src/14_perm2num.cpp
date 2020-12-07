#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "perm2num"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n;
    cin >> n;

    vector<size_t> v(n);
    for (auto &e : v) {
        cin >> e;
    }

    uint64_t k = 0;
    vector<bool> used(n);

    vector<uint64_t> f(1 + n);
    f[0] = f[1] = 1;

    for (size_t i = 2; i <= n; ++i) {
        f[i] = f[i - 1] * i;
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < v[i] - 1; ++j) {
            if (!used[j]) {
                k += f[n - i - 1];
            }
        }
        used[v[i] - 1] = true;
    }

    cout << k;

    return 0;
}
