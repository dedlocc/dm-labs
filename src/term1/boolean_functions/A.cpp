#include <bits/stdc++.h>

using namespace std;

class BinaryRelation
{
    vector<vector<bool>> m;
public:
    explicit BinaryRelation(const size_t &size) : m(size, vector<bool>(size))
    {

    }

    [[nodiscard]] bool isReflective() const
    {
        for (size_t i = 0; i < m.size(); ++i) {
            if (!m[i][i]) {
                return false;
            }
        }

        return true;
    }

    [[nodiscard]] bool isAntiReflective() const
    {
        for (size_t i = 0; i < m.size(); ++i) {
            if (m[i][i]) {
                return false;
            }
        }

        return true;
    }

    [[nodiscard]] bool isSymmetric() const
    {
        for (size_t i = 0; i < m.size(); ++i) {
            for (size_t j = i + 1; j < m.size(); ++j) {
                if (m[i][j] != m[j][i]) {
                    return false;
                }
            }
        }

        return true;
    }

    [[nodiscard]] bool isAntiSymmetric() const
    {
        for (size_t i = 0; i < m.size(); ++i) {
            for (size_t j = i + 1; j < m.size(); ++j) {
                if (i != j && m[i][j] && m[j][i]) {
                    return false;
                }
            }
        }

        return true;
    }

    [[nodiscard]] bool isTransitive() const
    {
        for (size_t i = 0; i < m.size(); ++i) {
            for (size_t j = 0; j < m.size(); ++j) {
                if (m[i][j]) {
                    for (size_t k = 0; k < m.size(); ++k) {
                        if (m[j][k] && !m[i][k]) {
                            return false;
                        }
                    }
                }
            }
        }

        return true;
    }

    BinaryRelation operator*(const BinaryRelation &br) const
    {
        assert(m.size() == br.m.size());

        auto result = BinaryRelation(m.size());

        for (size_t i = 0; i < m.size(); ++i) {
            for (size_t j = 0; j < m.size(); ++j) {
                bool r = false;
                for (size_t k = 0; k < m.size(); ++k) {
                    if (m[i][k] && br.m[k][j]) {
                        r = true;
                        break;
                    }
                }
                result.m[i][j] = r;
            }
        }

        return result;
    }

    void printInfo(ostream &out) const
    {
        out
            << isReflective() << ' '
            << isAntiReflective() << ' '
            << isSymmetric() << ' '
            << isAntiSymmetric() << ' '
            << isTransitive() << '\n';
    }

    friend ostream &operator<<(ostream &out, const BinaryRelation &br)
    {
        for (auto &i : br.m) {
            for (auto &&j : i) {
                out << j << ' ';
            }
            out << '\n';
        }
        return out;
    }

    friend istream &operator>>(istream &in, BinaryRelation &br)
    {
        for (auto &i : br.m) {
            for (auto &&j : i) {
                bool t;
                in >> t;
                j = t;
            }
        }
        return in;
    }
};

int main()
{
    size_t n;
    cin >> n;

    BinaryRelation r1(n), r2(n);
    cin >> r1 >> r2;

    r1.printInfo(cout);
    r2.printInfo(cout);

    cout << r1 * r2;

    return 0;
}
