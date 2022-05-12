#include <iostream>
#include <utility>
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

    friend FormalSeries operator+(FormalSeries const & p, FormalSeries const & q)
    {
        FormalSeries res(max(p.deg(), q.deg()));

        for (size_t i = 0; i < res.size(); ++i) {
            res[i] = p[i] + q[i];
        }

        return res;
    }

    friend void mulMod(FormalSeries & p, FormalSeries const & q, size_t maxDeg = 100)
    {
        FormalSeries res(min(p.deg() + q.deg(), maxDeg));

        for (size_t i = 0; i < res.size(); ++i) {
            for (size_t j = 0; j <= i; ++j) {
                res[i] += as_const(p)[j] * q[i - j];
            }
        }

        p = std::move(res);
    }

    friend void pow(FormalSeries & p, size_t power)
    {
        FormalSeries q = p;

        for (size_t i = 2; i <= power; ++i) {
            mulMod(p, q);
        }
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
    int64_t r;
    size_t d;
    cin >> r >> d;

    FormalSeries<int64_t> a(d);
    cin >> a;

    FormalSeries<int64_t> q = {1, -r};
    pow(q, a.deg() + 1);

    FormalSeries<int64_t> p(a.size());
    int64_t rPow = 1;
    for (size_t i = 0; i < p.size(); ++i) {
        int64_t n = 1;
        for (size_t j = 0; j < a.size(); ++j) {
            p[i] += n * a[j];
            n *= static_cast<int64_t>(i);
        }
        p[i] *= rPow;
        rPow *= r;
    }

    mulMod(p, q, q.deg());

    size_t lastNonZero = p.deg();
    while (lastNonZero > 0 && p[lastNonZero] == 0) {
        --lastNonZero;
    }
    p.resize(lastNonZero);

    cout << p << q;

    return 0;
}
