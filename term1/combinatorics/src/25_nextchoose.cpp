#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "nextchoose"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n, k;
    cin >> n >> k;

    vector<bool> v(n);

    for (size_t i = 0; i < k; ++i) {
        size_t t;
        cin >> t;
        v[t - 1] = true;
    }

    if (prev_permutation(v.begin(), v.end())) {
        for (size_t i = 0; i < n; ++i) {
            if (v[i]) {
                cout << 1 + i << ' ';
            }
        }
    } else {
        cout << -1;
    }

    return 0;
}