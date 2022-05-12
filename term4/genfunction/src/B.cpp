#include <iostream>
#include <vector>

using namespace std;

constexpr int64_t MOD = 998'244'353;

struct EEA
{
    int64_t gcd;
    int64_t x, y;

    static EEA run(int64_t a, int64_t b)
    {
        if (a == 0) {
            return {b, 0, 1};
        }
        EEA eea = run(b % a, a);
        return {eea.gcd, eea.y - (b / a) * eea.x, eea.x};
    }
};

int64_t modInverse(int64_t n)
{
    EEA eea = EEA::run(n, MOD);
    return (eea.x % MOD + MOD) % MOD;
}

template <class T>
class FormalSeries
{
    vector<T> coefficients;

public:
    FormalSeries(initializer_list<T> coefficients)
        : coefficients(std::move(coefficients))
    {}

    explicit FormalSeries(size_t degree = 0)
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

    void resize(size_t degree)
    {
        coefficients.resize(degree + 1);
    }

    T & operator[](size_t i)
    {
        return coefficients[i];
    }

    T operator[](size_t i) const
    {
        return i >= size() ? 0 : coefficients[i];
    }

    FormalSeries const & operator+=(FormalSeries const & other)
    {
        resize(max(deg(), other.deg()));

        for (size_t i = 0; i < size(); ++i) {
            coefficients[i] += other[i];
            coefficients[i] %= MOD;
        }

        return *this;
    }

    friend FormalSeries operator*(T const & n, FormalSeries const & q)
    {
        FormalSeries res = q;

        for (size_t i = 0; i < res.size(); ++i) {
            res[i] *= n;
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

    friend istream & operator>>(istream & in, FormalSeries & series)
    {
        for (size_t i = 0; i < series.size(); ++i) {
            in >> series[i];
        }
        return in;
    }

    friend void print(ostream & out, FormalSeries const & series, size_t m)
    {
        for (size_t i = 0; i < min(m, series.size()); ++i) {
            out << series[i] << ' ';
        }
        out << '\n';
    }
};

int main()
{
    size_t n, m;
    cin >> n >> m;

    FormalSeries<int64_t> p(n);
    cin >> p;

    vector<int64_t> sqrt(m), exp(m), log(m);

    sqrt[0] = exp[0] = 1;

    for (size_t i = 1; i < m; ++i) {
        sqrt[i] = sqrt[i - 1] * (3 * modInverse(i * 2) - 1);
        sqrt[i] %= MOD;
        exp[i] = exp[i - 1] * modInverse(i);
        exp[i] %= MOD;
    }

    if (m > 1) {
        log[1] = 1;

        for (size_t i = 2; i < m; ++i) {
            log[i] = log[i - 1] * (modInverse(i) - 1);
            log[i] %= MOD;
        }
    }

    FormalSeries<int64_t> sqrtS, expS, logS;
    FormalSeries<int64_t> pow = {1};

    for (size_t i = 0; i < m; ++i) {
        sqrtS += sqrt[i] * pow;
        expS += exp[i] * pow;
        logS += log[i] * pow;
        pow = pow * p;
        pow.resize(m);
    }

    print(cout, sqrtS, m);
    print(cout, expS, m);
    print(cout, logS, m);

    return 0;
}
