#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "choose2num"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n, k;
    cin >> n >> k;

    vector<size_t> v(n);

    for (auto &e : v) {
        cin >> e;
    }

    vector<vector<size_t>> c(n, vector<size_t>(k, 1));

    for (size_t i = 2; i < n; ++i) {
        for (size_t j = 1; j < i && j < k; ++j) {
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
    }

    size_t m = 0;

    for (size_t i = 0; i < k; ++i) {
        for (size_t j = 0 == i ? 1 : 1 + v[i - 1]; j < v[i]; ++j) {
            m += c[n - j][k - i - 1];
        }
    }

    cout << m;

    return 0;
}
