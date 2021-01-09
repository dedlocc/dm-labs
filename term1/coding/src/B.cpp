#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    multiset<string> v;
    v.emplace(s);

    for (size_t i = 1; i < s.length(); ++i) {
        rotate(s.begin(), 1 + s.begin(), s.end());
        v.emplace(s);
    }

    for (const auto &e : v) {
        cout << e.back();
    }

    return 0;
}
