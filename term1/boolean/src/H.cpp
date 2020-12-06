#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n;
    cin >> n;

    string s = "((A0|B0)|(A0|B0))";

    for (size_t i = 1; i < n; ++i) {
        const string is = to_string(i);
        s.insert(0, 2, '(').append("|((A").append(is).append("|A").append(is).append(")|(B").append(is).append("|B")
            .append(is).append(")))|(A").append(is).append("|B").append(is).append("))");
    }

    cout << s;

    return 0;
}
