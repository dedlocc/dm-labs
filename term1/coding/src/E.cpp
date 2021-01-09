#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unordered_map<string, size_t> dict;
    for (auto i = 'a'; i <= 'z'; ++i) {
        dict[string(1, i)] = dict.size();
    }

    string t;
    uint8_t c;
    while (cin >> c) {
        string d = t;
        d += c;
        if (t.empty() || dict.end() != dict.find(d)) {
            t = d;
        } else {
            cout << dict[t] << ' ';
            dict[d] = dict.size();
            t = c;
        }
    }

    cout << (dict.end() == dict.find(t) ? dict.size() : dict[t]);

    return 0;
}
