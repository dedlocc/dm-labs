#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "nextvector"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

void foo(vector<bool> v, const bool &neg)
{
    bool c = true;

    for (auto i = v.rbegin(); i != v.rend(); ++i) {
        const auto t = *i != c;
        c = neg != *i && c;
        *i = t;
    }

    if (c) {
        cout << '-';
    } else {
        for (const auto &e : v) {
            cout << e;
        }
    }

    cout << '\n';
}

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    unsigned char b;
    vector<bool> v;

    while (cin >> b) {
        v.push_back('1' == b);
    }

    foo(v, true);
    foo(v, false);

    return 0;
}