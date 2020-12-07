#include <bits/stdc++.h>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "nextsetpartition"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    size_t n;
    while (cin >> n && 0 != n) {
        size_t k;
        cin >> k;
        vector<deque<size_t>> v(k);

        cin.ignore();
        for (auto &e : v) {
            string s;
            getline(cin, s);
            istringstream in(s);
            size_t t;
            while (in >> t) {
                e.push_back(t);
            }
        }

        vector<size_t> used;
        bool f = false;
        for (auto i = v.rbegin(); i != v.rend(); ++i) {
            auto min = used.end();
            for (auto j = used.begin(); j != used.end(); ++j) {
                if (*j > i->back() && (min == used.end() || *min > *j)) {
                    min = j;
                }
            }

            if (!used.empty() && min != used.end()) {
                i->push_back(*min);
                used.erase(min);
                break;
            }

            for (auto j = i->rbegin(); j != i->rend(); ++j) {
                min = used.end();
                for (auto z = used.begin(); z != used.end(); ++z) {
                    if (*z > *j && (min == used.end() || *min > *z)) {
                        min = z;
                    }
                }
                if (!used.empty() && min != used.end() && j != i->rend() - 1) {
                    const auto t = *j;
                    *j = *min;
                    used.erase(min);
                    used.push_back(t);
                    f = true;
                    break;
                }
                used.push_back(*j);
                i->erase(next(j).base());
            }

            if (i->empty()) {
                v.erase(next(i).base());
            }

            if (f) {
                break;
            }
        }

        sort(used.begin(), used.end());

        for (const auto &e : used) {
            v.push_back({e});
        }

        cout << n << ' ' << v.size() << '\n';
        for (const auto &i : v) {
            for (const auto &j : i) {
                cout << j << ' ';
            }
            cout << '\n';
        }
        cout << '\n';
    }

    return 0;
}
