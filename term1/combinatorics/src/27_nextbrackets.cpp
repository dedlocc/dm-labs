#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "nextbrackets"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    string s;
    cin >> s;

    size_t open = 0, closed = 0;

    for (auto i = s.rbegin(); i != s.rend(); ++i) {
        if ('(' == *i) {
            ++open;
            if (closed > open) {
                break;
            }
        } else {
            ++closed;
        }
    }

    s.erase(s.end() - open - closed, s.end());

    if (s.empty()) {
        cout << "-";
    } else {
        cout << s << ')' << string(open, '(') << string(closed - 1, ')');
    }

    return 0;
}
