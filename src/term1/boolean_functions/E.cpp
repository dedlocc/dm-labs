#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n;
    cin >> n;

    const size_t m = 1u << n;

    vector<bool> v(m);
    vector<string> v2(m);

    for (size_t i = 0; i < m; ++i) {
        bool t;
        cin >> v2[i] >> t;
        v[i] = t;
    }

    for (size_t i = 0; i < m; ++i) {
        cout << v2[i] << ' ' << v[0] << '\n';
        for (size_t j = 0; j < m - i - 1; ++j) {
            v[j] = v[j] != v[j + 1];
        }
    }

    return 0;
}
