#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "brackets2num2"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    string s;
    cin >> s;

    const size_t n = s.size();

    vector<vector<uint64_t>> d(n, vector<uint64_t>(1 + n));
    d[0][0] = 1;
    for (size_t i = 1; i < n; ++i) {
        d[i][0] = d[i - 1][1];
        d[i][n] = d[i - 1][n - 1];
        for (size_t j = 1; j < n; ++j) {
            d[i][j] = d[i - 1][j - 1] + d[i - 1][j + 1];
        }
    }

    uint64_t k = 0;
    stack<bool> b;

    for (size_t i = 0, j = n - 1; i < n; ++i, --j) {
        if ('(' == s[i]) {
            b.push(true);
            continue;
        }

        const auto t = d[j][b.size() + 1] << (j - b.size() - 1) / 2;
        k += t;

        if (!b.empty() && b.top()) {
            if (')' == s[i]) {
                b.pop();
                continue;
            }
            k += d[j][b.size() - 1] << (j - b.size() + 1) / 2;
        }

        if ('[' == s[i]) {
            b.push(false);
        } else {
            k += t;
            b.pop();
        }
    }

    cout << k;

    return 0;
}
