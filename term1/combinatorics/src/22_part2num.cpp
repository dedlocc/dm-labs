#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "part2num"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    vector<size_t> v;
    char c;

    do {
        size_t t;
        cin >> t;
        v.push_back(t);
    } while (cin >> c);

    vector<size_t> u(reduce(v.begin(), v.end()), 1);
    size_t counter = 0;

    while (u != v) {
        auto a = u.end() - 1;
        auto b = u.end() - 2;

        if (--*a < ++*b) {
            *b-- += *a--;
            u.pop_back();
        } else {
            while (*b << 1u <= *a) {
                u.push_back(*a - *b);
                *(a = u.end() - 2)++ = *(b = u.end() - 3)++;
            }
        }

        ++counter;
    }

    cout << counter;

    return 0;
}
