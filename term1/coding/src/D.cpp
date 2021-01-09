#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<uint8_t> v('z' - 'a' + 1);
    iota(v.begin(), v.end(), 'a');

    uint8_t c;
    while (cin >> c) {
        const auto e = find(v.begin(), v.end(), c);
        cout << (e - v.begin() + 1) << ' ';
        rotate(v.begin(), e, e + 1);
    }

    return 0;
}
