#include <bits/stdc++.h>

using namespace std;

enum Literal
{
    NONE = -1,
    FALSE = 0,
    TRUE = 1
};

int main()
{
    size_t n, k;
    cin >> n >> k;

    vector<vector<Literal>> h(k, vector<Literal>(n));

    for (auto &i : h) {
        for (auto &j : i) {
            int t;
            cin >> t;
            j = (Literal) t;
        }
    }

    while(true) {
        vector<Literal> vars(n, NONE);

        // Find all singles and their values
        for (const auto &i : h) {
            const Literal *l = nullptr;
            bool isSingle = true;
            for (const auto &j : i) {
                if (NONE != j) {
                    if (nullptr == l) {
                        l = &j;
                    } else {
                        isSingle = false;
                        break;
                    }
                }
            }
            if (isSingle) {
                vars[l - &i.front()] = *l;
            }
        }

        // If no singles are left - return NO
        if (vars.empty()) {
            cout << "NO";
            return 0;
        }
        bool noSingles = true;
        for (const auto &v : vars) {
            if (NONE != v) {
                noSingles = false;
                break;
            }
        }
        if (noSingles) {
            cout << "NO";
            return 0;
        }

        // If at least any conjunct is equal to 0, return YES
        for (const auto &i : h) {
            bool f = false;
            for (size_t j = 0; j < n; ++j) {
                if (NONE != i[j] && (NONE == vars[j] || i[j] == vars[j])) {
                    f = true;
                    break;
                }
            }
            if (!f) {
                cout << "YES";
                return 0;
            }
        }

        // Remove all single vars and conjuncts equal to 1
        for (auto i = h.begin(); i != h.end();) {
            bool f1 = false;
            bool f2 = true;
            for (size_t j = 0; j < i[0].size(); ++j) {
                if (NONE != vars[j]) {
                    if (vars[j] == i[0][j]) {
                        f1 = true;
                        break;
                    } else {
                        i[0][j] = NONE;
                    }
                } else if (f2 && NONE != i[0][j]) {
                    f2 = false;
                }
            }
            if (f1 || f2) {
                i = h.erase(i);
            } else {
                ++i;
            }
        }
    }
}
