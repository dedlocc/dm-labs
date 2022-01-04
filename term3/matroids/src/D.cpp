#include <iostream>
#include <set>
#include <unordered_set>
#include <algorithm>

#ifdef LOCAL
#define FILE_IN "input.txt"
#define FILE_OUT "output.txt"
#else
#define FILE "check"
#define FILE_IN FILE ".in"
#define FILE_OUT FILE ".out"
#endif

using namespace std;

bool solution()
{
    size_t n, m;
    cin >> n >> m;

    if (m == 0) {
        return false;
    }

    using SubX = set<uint32_t>;

    auto hash = [](SubX const &sx) {
        size_t hash = 0;
        for (auto e : sx) {
            hash *= 10;
            hash += e;
        }
        return hash;
    };

    unordered_multiset<SubX, decltype(hash)> s(0, hash);
    bool hasEmpty = false;

    for (size_t i = 0; i < m; ++i) {
        size_t k;
        cin >> k;
        SubX sx;
        for (size_t j = 0; j < k; ++j) {
            uint32_t t;
            cin >> t;
            sx.insert(t);
        }
        if (sx.empty()) {
            hasEmpty = true;
        }
        s.insert(move(sx));
    }

    if (!hasEmpty) {
        return false;
    }

    for (auto it = s.begin(); it != s.end(); ++it) {
        auto sx = *it;
        for (auto e : *it) {
            sx.erase(e);
            if (s.find(sx) == s.end()) {
                return false;
            }
            sx.insert(e);
        }
        for (auto it2 = s.begin(); it2 != s.end(); ++it2) {
            if (it->size() <= it2->size()) {
                continue;
            }
            sx = *it2;
            auto sy = *it;
            for (auto e : *it) {
                sy.erase(e);
                sy.insert(e);
            }
            for (auto e : sx) {
                sy.erase(e);
            }
            for (auto e : sy) {
                sx.insert(e);
                if (s.find(sx) != s.end()) {
                    goto success;
                }
                sx.erase(e);
            }
            return false;
            success:;
        }
    }

    return true;
}

int main()
{
    freopen(FILE_IN, "r", stdin), freopen(FILE_OUT, "w", stdout);

    cout << (solution() ? "YES" : "NO") << '\n';

    return 0;
}