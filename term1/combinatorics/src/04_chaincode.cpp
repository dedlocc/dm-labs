#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "chaincode"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n;
    cin >> n;

    vector<bool> current(n, false);
    unordered_set<vector<bool>> result;

    while (true) {
        for (size_t i = 1; i < n; ++i) {
            current[i - 1] = current[i];
        }

        current.back() = true;

        if (result.end() != result.find(current)) {
            current.back() = false;

            if (result.end() != result.find(current)) {
                break;
            }
        }

        result.insert(current);

        for (const auto &e : current) {
            cout << e;
        }
        cout << '\n';
    }

    return 0;
}
