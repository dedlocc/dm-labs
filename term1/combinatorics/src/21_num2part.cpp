#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "num2part"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n, k;
    cin >> n >> k;

    vector<size_t> v(n, 1u);

    for (size_t i = 0; i < k; ++i) {
        auto a = v.end() - 1;
        auto b = v.end() - 2;

        if (--*a < ++*b) {
            *b-- += *a--;
            v.pop_back();
        } else {
            while (*b << 1u <= *a) {
                v.push_back(*a - *b);
                *(a = v.end() - 2)++ = *(b = v.end() - 3)++;
            }
        }
    }

    cout << v[0];
    for (size_t i = 1; i < v.size(); ++i) {
        cout << '+' << v[i];
    }

    return 0;
}
