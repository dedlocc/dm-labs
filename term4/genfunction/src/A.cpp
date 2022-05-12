#include <iostream>
#include <vector>

using namespace std;

template <class T>
class FormalSeries
{
    vector<T> coefficients;
    static constexpr T MOD = 998'244'353;

public:
    explicit FormalSeries(size_t degree)
        : coefficients(degree + 1)
    {}

    [[nodiscard]] size_t size() const
    {
        return coefficients.size();
    }

    [[nodiscard]] size_t deg() const
    {
        return size() - 1;
    }

    T & operator[](size_t i)
    {
        return coefficients[i];
    }

    T operator[](size_t i) const
    {
        return i >= size() ? 0 : coefficients[i];
    }

    friend FormalSeries operator+(FormalSeries const & p, FormalSeries const & q)
    {
        FormalSeries res(max(p.deg(), q.deg()));

        for (size_t i = 0; i < res.size(); ++i) {
            res[i] = (p[i] + q[i]) % MOD;
        }

        return res;
    }

    friend FormalSeries operator*(FormalSeries const & p, FormalSeries const & q)
    {
        FormalSeries res(p.deg() + q.deg());

        for (size_t i = 0; i < res.size(); ++i) {
            for (size_t j = 0; j <= i; ++j) {
                res[i] += (p[j] * q[i - j]) % MOD;
                res[i] %= MOD;
            }
        }

        return res;
    }

    friend FormalSeries operator/(FormalSeries const & p, FormalSeries const & q)
    {
        FormalSeries res(1000 - 1);

        for (size_t i = 0; i < res.size(); ++i) {
            res[i] = p[i];
            for (size_t j = 0; j < i; ++j) {
                res[i] -= (res[j] * q[i - j]) % MOD;
                res[i] += MOD;
                res[i] %= MOD;
            }
            res[i] /= q[0];
        }

        return res;
    }

    friend istream & operator>>(istream & in, FormalSeries & series)
    {
        for (size_t i = 0; i < series.size(); ++i) {
            in >> series[i];
        }
        return in;
    }

    friend ostream & operator<<(ostream & out, FormalSeries const & series)
    {
        out << series.deg() << '\n';
        for (size_t i = 0; i < series.size(); ++i) {
            out << series[i] << ' ';
        }
        return out << '\n';
    }
};

int main()
{
    size_t n, m;
    cin >> n >> m;

    FormalSeries<int64_t> p(n), q(m);
    cin >> p >> q;

    cout << p + q << p * q;

    auto div = p / q;
    for (size_t i = 0; i < div.size(); ++i) {
        cout << div[i] << ' ';
    }

    return 0;
}
