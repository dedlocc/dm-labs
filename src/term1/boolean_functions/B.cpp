#include <bits/stdc++.h>

using namespace std;

class BooleanFunction
{
    vector<bool> m;
    size_t size;

    [[nodiscard]] bool static getParity(unsigned n)
    {
        for (size_t i = 1; i < 32; i <<= 1u) {
            n ^= (n >> i);
        }

        return 1u & n;
    }

    [[nodiscard]] bool isConst() const
    {
        for (size_t i = 1; i < m.size(); ++i) {
            if (m[i] != m[0]) {
                return false;
            }
        }

        return true;
    }

public:
    explicit BooleanFunction(const size_t &size) : size(size), m(1u << size)
    {

    }

    [[nodiscard]] bool preservesZero() const
    {
        return !m.front();
    }

    [[nodiscard]] bool preservesOne() const
    {
        return m.back();
    }

    [[nodiscard]] bool isMonotone() const
    {
        for (size_t i = 0; i < m.size(); ++i) {
            if (!m[i]) {
                for (size_t j = 0; j < size; ++j) {
                    if (m[i & ~(1u << j)]) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    [[nodiscard]] bool isSelfDual() const
    {
        if (isConst()) {
            return false;
        }

        for (size_t i = 0; i < m.size() >> 1u; ++i) {
            if (m[i] == m[m.size() - i - 1]) {
                return false;
            }
        }

        return true;
    }

    [[nodiscard]] bool isLinear() const
    {
        vector<bool> t = m;
        for (size_t i = 0; i < m.size(); ++i) {
            if (t[0] && 0 != (i & (i - 1))) {
                return false;
            }
            for (size_t j = 0; j < m.size() - i - 1; ++j) {
                t[j] = t[j] != t[j + 1];
            }
        }

        return true;
    }

    [[nodiscard]] bitset<5> getInfo() const
    {
        auto b = bitset<5>();
        b[4] = preservesZero();
        b[3] = preservesOne();
        b[2] = isMonotone();
        b[1] = isSelfDual();
        b[0] = isLinear();

        return b;
    }

    friend istream &operator>>(istream &in, BooleanFunction &bf)
    {
        for (auto &&i : bf.m) {
            unsigned char t;
            cin >> t;
            i = '1' == t;
        }
        return cin;
    }

};

int main()
{
    size_t n;
    cin >> n;

    bitset<5> info;
    info.set();

    for (size_t i = 0; i < n; ++i) {
        size_t s;
        cin >> s;
        BooleanFunction a(s);
        cin >> a;
        info &= a.getInfo();
    }

    cout << (info.none() ? "YES" : "NO") << '\n';

    return 0;
}
