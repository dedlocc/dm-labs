#include <iostream>
#include <vector>

using namespace std;

constexpr int64_t MOD = 104'857'601;

template <class T>
class FormalSeries
{
    vector<T> coefficients;

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
};

int main()
{
    size_t k, n;
    cin >> k >> n;
    --n;

    vector<int64_t> a(k * 2);
    for (size_t i = 0; i < k; ++i) {
        cin >> a[i];
    }

    FormalSeries<int64_t> c(k);
    c[0] = 1;
    for (size_t i = 1; i < c.size(); ++i) {
        cin >> c[i];
        c[i] = MOD - c[i];
    }

    while (n >= k) {
        for (size_t i = k; i < k * 2; ++i) {
            a[i] = 0;
            for (size_t j = 1; j < c.size(); ++j) {
                a[i] += ((MOD - c[j]) * a[i - j]) % MOD;
                a[i] %= MOD;
            }
        }

        for (size_t i = n % 2; i < k * 2; i += 2) {
            a[i / 2] = a[i];
        }

        {
            auto nc = c;
            for (size_t i = 1; i <= k; i += 2) {
                nc[i] = MOD - nc[i];
            }
            c = c * nc;
        }

        for (size_t i = 1; i <= k; ++i) {
            c[i] = c[i * 2];
        }

        c.resize(k);

        n /= 2;
    }

    cout << a[n];

    return 0;
}
