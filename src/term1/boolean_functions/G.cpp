#include <bits/stdc++.h>

using namespace std;

class BoolVal
{
    bool _isSet = false;
    bool value = false;
public:
    bool operator==(const bool &v) const
    {
        return _isSet && value == v;
    }

    bool operator!=(const bool &v) const
    {
        return !operator==(v);
    }

    BoolVal& operator=(const bool &v)
    {
        value = v;
        _isSet = true;
        return *this;
    }

    explicit operator const bool&() const
    {
        return value;
    }

    [[nodiscard]] bool isSet() const
    {
        return _isSet;
    }
};

int main()
{
    size_t n;
    cin >> n;

    vector<uint64_t> a(n);

    for (auto &i : a) {
        cin >> i;
    }

    uint64_t s;
    cin >> s;

    vector<BoolVal> v(1u << n);

    for (size_t i = 0; i < 33; ++i) {
        const uint64_t b = 1ull << i;
        size_t index = 0;
        size_t k = 0;
        for (const auto &j : a) {
            if (j & b) {
                index |= 1u << k;
            }
            ++k;
        }
        const bool r = s & b;
        if (v[index].isSet()) {
            if (v[index] != r) {
                cout << "Impossible";
                return 0;
            }
        } else {
            v[index] = r;
        }
    }

    if (all_of(v.begin(), v.end(), [](BoolVal b) { return !b; })) {
        cout << "1&~1";
        return 0;
    }

    bool first = true;

    for (size_t i = 0; i < v.size(); ++i) {
        if (!v[i]) {
            continue;
        }

        if (first) {
            first = false;
        } else {
            cout << '|';
        }

        for (size_t j = n; j > 0; --j) {
            if (0 == (i & (1u << (j - 1)))) {
                cout << '~';
            }

            cout << j;

            if (1 != j) {
                cout << '&';
            }
        }
    }

    return 0;
}
