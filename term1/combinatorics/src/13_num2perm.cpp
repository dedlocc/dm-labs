#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "num2perm"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n;
    uint64_t k;
    cin >> n >> k;

    vector<size_t> v(n);
    vector<bool> used(n);

    vector<uint64_t> f(1 + n);
    f[0] = f[1] = 1;

    for (size_t i = 2; i <= n; ++i) {
        f[i] = f[i - 1] * i;
    }

    for (size_t i = 0; i < n; ++i) {
        const auto a = k / f[n - i - 1];
        k %= f[n - i - 1];

        size_t c = 0;
        for (size_t j = 0; j < n; ++j) {
            if (!used[j] && c++ == a) {
                v[i] = 1 + j;
                used[j] = true;
            }
        }
    }

    for (const auto &e : v) {
        cout << e << ' ';
    }

    return 0;
}
