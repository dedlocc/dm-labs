#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<string> dict(26);
    iota(dict.begin(), dict.end(), 'a');

    string s;

    for (size_t i = 0; i < n; ++i) {
        size_t k;
        cin >> k;
        if (k == dict.size()) {
            dict.push_back(s + s[0]);
        } else if (!s.empty()) {
            dict.push_back(s + dict[k][0]);
        }

        s = dict[k];
        cout << s;
    }

    return 0;
}
