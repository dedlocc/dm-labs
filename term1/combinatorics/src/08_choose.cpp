#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "choose"
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
    fill(v.begin(), v.begin() + k, true);

    do {
        for (size_t i = 0; i < n; ++i) {
            if (v[i]) {
                cout << 1 + i << ' ';
            }
        }
        cout << '\n';
    } while (prev_permutation(v.begin(), v.end()));

    return 0;
}