#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template <class T>
class FormalSeries
{
    vector<T> coefficients;
    static constexpr T MOD = 998'244'353;

public:
    FormalSeries(initializer_list<T> coefficients)
        : coefficients(std::move(coefficients))
    {}

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

    friend FormalSeries & operator-=(FormalSeries & p, FormalSeries const & q)
    {
        FormalSeries res(max(p.deg(), q.deg() + 1));

        for (size_t i = 0; i < res.size(); ++i) {
            res[i] = (as_const(p)[i] - q[i - 1] + MOD) % MOD;
            res[i] %= MOD;
        }

        return p = std::move(res);
    }

    friend FormalSeries div(FormalSeries const & p, FormalSeries const & q, size_t n)
    {
        FormalSeries res(n);

        for (size_t i = 0; i < res.size(); ++i) {
            res[i] = p[i];
            for (size_t j = 0; j < i; ++j) {
                res[i] -= (res[j] * q[i - j]) % MOD;
                res[i] %= MOD;
                res[i] += MOD;
                res[i] %= MOD;
            }
            res[i] /= q[0];
        }

        return res;
    }

    friend ostream & operator<<(ostream & out, FormalSeries const & series)
    {
        for (size_t i = 0; i < series.size(); ++i) {
            out << series[i] << '\n';
        }
        return out << '\n';
    }
};

int main()
{
    size_t k, n;
    cin >> k >> n;

    FormalSeries<int64_t> q1 = {1}, q2 = {1};
    for (size_t i = 2; i < k; ++i) {
        auto q3 = q2;
        q2 -= q1;
        q1 = std::move(q3);
    }

    cout << div(q1, q2, n - 1);

    return 0;
}
