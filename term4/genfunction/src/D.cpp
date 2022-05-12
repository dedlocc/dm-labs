#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

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
        }

        return *this;
    }

    FormalSeries const & operator*=(FormalSeries const & q)
    {
        FormalSeries res(deg() + q.deg());

        for (size_t i = 0; i < res.size(); ++i) {
            for (size_t j = 0; j <= i; ++j) {
                res[i] += std::as_const(*this)[j] * q[i - j];
            }
        }

        return *this = res;
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
    int r;
    size_t k;
    cin >> r >> k;

    vector<int64_t> p(k + 1);
    for (auto &e : p) {
        cin >> e;
    }

    int64_t denom = 1, pow = 1;
    for (size_t i = 1; i < p.size(); ++i) {
        denom *= static_cast<int64_t>(i);
        pow *= r;
        p[k - i] *= pow;
    }
    denom *= pow;

    FormalSeries<int64_t> res;

    for (size_t i = 0; i < p.size(); ++i) {
        FormalSeries<int64_t> prod = {p[i]};
        for (size_t j = 1; j < p.size(); ++j) {
            prod *= FormalSeries<int64_t> {static_cast<int64_t>(j - i), 1};
        }
        res += prod;
    }

    for (size_t i = 0; i < res.size(); ++i) {
        auto gcd = std::gcd(res[i], denom);
        std::cout << res[i] / gcd << '/' << denom / gcd << ' ';
    }

    return 0;
}
